#define CURL_STATICLIB

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <curl/curl.h>

#pragma warning(disable : 4996)

using namespace std;

// object of mutex - will use for protect access to shared data (cout obj) at the same time from different threads
mutex sync_cout_mutex;

// Define our struct for accepting LCs output
struct BufferStruct
{
	char* buffer = nullptr;
	size_t size = 0;
};

// This is the function we pass to LC, which writes the output to a File
static size_t WriteToFileCallback(void* chunk_data, size_t size, size_t chunk_size, void* our_file)
{
	static size_t callNumber = 0;
	const size_t chunkSize = size * chunk_size;
	ofstream* myfile = static_cast<ofstream*>(our_file);

	{
		lock_guard<mutex> locker(sync_cout_mutex); // RAII idiom, automatically lock/unlock sync_cout_mutex - all common data - locked till mutex will be unlocked
		std::cout << "chunkDataFromNetwork = " << chunk_data << " size = " << size << "chunk_size = " << chunk_size << " callNumber = " 
				<< callNumber << " Thread3 ID = " << this_thread::get_id() << std::endl;
	}

	callNumber++;

	myfile->write(static_cast<char*>(chunk_data), chunk_size);

	return chunkSize;
}

void SaveToFileUsingOfstream(const char* url, ofstream* file)
{
	CURL* httpHandle = curl_easy_init(); // Start a libcurl easy session, This function must be the first function to call. Return CURL easy handle

	curl_easy_setopt(httpHandle, CURLOPT_WRITEFUNCTION, WriteToFileCallback); // Passing the function pointer to LC
	curl_easy_setopt(httpHandle, CURLOPT_WRITEDATA, file); // Passing our BufferStruct to LC
	curl_easy_setopt(httpHandle, CURLOPT_URL, url); // Set URL http://placebeard.it/640/480, https://www.w3.org/TR/PNG/iso_8859-1.txt

	CURLcode result = curl_easy_perform(httpHandle); // execute out HTTP request, blocking function
	curl_easy_cleanup(httpHandle); // End a libcurl easy handle
}

// This is the function we pass to LC, which writes the output to a BufferStruct
static size_t WriteToMemoryCallback(void* chunk_data, size_t size, size_t chunk_size, void* ourBufferToSave)
{
	static size_t callNumber = 0;
	const size_t chunkSize = size * chunk_size;
	struct BufferStruct* mem = static_cast<BufferStruct*>(ourBufferToSave);

	{
		lock_guard<mutex> locker(sync_cout_mutex); // RAII idiom, automatically lock/unlock sync_cout_mutex - all common data - locked till mutex will be unlocked
		std::cout << "chunkDataFromNetwork = " << chunk_data << " size = " << size << "chunk_size = " << chunk_size << " ourBufferToSave = "
			<< ourBufferToSave << " callNumber = " << callNumber << "mem->size = " << mem->size << " Thread1 ID = " << this_thread::get_id() << std::endl;
	}

	callNumber++;
	mem->buffer = static_cast<char*>(realloc(mem->buffer, mem->size + chunkSize + 1)); //If want to download img - reduce - 1 - without 0\ ->B

	if (mem->buffer)
	{
		memcpy(mem->buffer + mem->size, chunk_data, chunkSize);
		mem->size += chunkSize;
		mem->buffer[mem->size] = 0; // ->B And not paste in the end - \0
	}
	return chunkSize;
}

void SaveInBuffer(char* url, BufferStruct* output)
{
	CURL* httpHandle = curl_easy_init(); // Start a libcurl easy session, This function must be the first function to call. Return CURL easy handle

	curl_easy_setopt(httpHandle, CURLOPT_WRITEFUNCTION, WriteToMemoryCallback); // Passing the function pointer to LC
	curl_easy_setopt(httpHandle, CURLOPT_WRITEDATA, output); // Passing our BufferStruct to LC
	curl_easy_setopt(httpHandle, CURLOPT_URL, url); // Set URL http://placebeard.it/640/480, https://www.w3.org/TR/PNG/iso_8859-1.txt

	CURLcode result = curl_easy_perform(httpHandle); // execute out HTTP request, blocking function
	curl_easy_cleanup(httpHandle); // End a libcurl easy handle
}

void SaveToFileUsingCFile(const char* url, const char* file_name) // without own callback
{
	CURL* httpHandle = curl_easy_init(); // Start a libcurl easy session, This function must be the first function to call. Return CURL easy handle
	curl_easy_setopt(httpHandle, CURLOPT_URL, url); // Set URL
	{
		lock_guard<mutex> locker(sync_cout_mutex); // RAII idiom, automatically lock/unlock sync_cout_mutex - all common data - locked till mutex will be unlocked
		cout << " Thread2 ID = " << this_thread::get_id() << " , saving to file using C file "<< endl;
	}
	FILE* file = fopen(file_name, "w");
	// Passing our file to LC, If not set CURLOPT_WRITEFUNCTION - will be used internal Libcurl callback func, that working with FILE*
	curl_easy_setopt(httpHandle, CURLOPT_WRITEDATA, file);
	CURLcode result = curl_easy_perform(httpHandle); // execute out HTTP request, blocking function
	curl_easy_cleanup(httpHandle); // End a libcurl easy handle
	fclose(file);
}

int main(int argc, char** argv)
{
	curl_global_init(CURL_GLOBAL_ALL); // at the startup when ONLY 1 THREAD EXISTS IN PROGRAM

	BufferStruct output;

	thread Thread1(SaveInBuffer, argv[1], &output);
	thread Thread2(SaveToFileUsingCFile, argv[2], argv[3]);

	ofstream file;
	file.open("FileFromThread3.txt", ios::out | ios::app); // ios::out | ios::app - will write from end of file. If file have some text, new text will write after
	thread Thread3(SaveToFileUsingOfstream, argv[2], &file);
	
	for (int i = 0; i < 10; i++)
	{
		lock_guard<mutex> locker(sync_cout_mutex); // RAII idiom, automatically lock/unlock sync_cout_mutex - all common data - locked till mutex will be unlocked
		cout << "i = " << i << " MAIN Thread ID = " << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	Thread1.join();
	Thread2.join();
	Thread3.join();

	free(output.buffer);

	cout << "argv[0] = " << argv[0] << endl;
	cout << "argv[1] = " << argv[1] << endl;
	cout << "argv[2] = " << argv[2] << endl;
	cout << "argv[3] = " << argv[3] << endl;

	return EXIT_SUCCESS;
}
