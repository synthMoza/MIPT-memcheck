#include <iostream>

//! The name of the output log file
#define LOG_FILE_NAME "memory.log"

//!Usage of macros:
//!<variable> = new <type>; => <variable> = NEW <type>
#define NEW new(__FILE__, __PRETTY_FUNCTION__, __LINE__)
//!delete(<variable>) => DELETE(<variable>)
#define DELETE(memory) operator delete (memory, __FILE__, __PRETTY_FUNCTION__, __LINE__)
//! delete[](<variable>) => DELETE_(<variable>)
#define DELETE_(memory) operator delete[](memory, __FILE__, __PRETTY_FUNCTION__, __LINE__)

void* operator new(size_t size, const std::string& file_name, const std::string& func_name, int com_line)
{
    FILE* log_file = nullptr;
    void* memory = nullptr;

    log_file = fopen(LOG_FILE_NAME, "a");

    memory = ::operator new(size);

    fprintf(log_file, "[%p] Memory allocating with \"new\": file "
                                  "\"%s\", function \"%s\", line %d, size %zu.\n", memory, file_name.c_str(), func_name.c_str(), com_line, size);
    fclose(log_file);

    return memory;
}

void * operator new[](size_t size, const std::string& file_name, const std::string& func_name, int com_line)
{
    FILE* log_file = nullptr;
    void* memory = nullptr;

    log_file = fopen(LOG_FILE_NAME, "a");

    memory = ::operator new[](size);

    fprintf(log_file, "[%p] Memory allocating with \"new[]\": file "
                      "\"%s\", function \"%s\", line %d, size %zu.\n", memory, file_name.c_str(), func_name.c_str(), com_line, size);
    fclose(log_file);

    return memory;
}

void operator delete(void* memory, const std::string& file_name, const std::string& func_name, int com_line)
{
    FILE* log_file = nullptr;

    log_file = fopen(LOG_FILE_NAME, "a");

    fprintf(log_file, "[%p] Memory free-up with \"delete\": file "
                      "\"%s\", function \"%s\", line %d.\n", memory, file_name.c_str(), func_name.c_str(), com_line);

    fclose(log_file);
    ::operator delete(memory);
}

void operator delete[](void* memory, const std::string& file_name, const std::string& func_name, int com_line)
{
    FILE* log_file = nullptr;

    log_file = fopen(LOG_FILE_NAME, "a");

    fprintf(log_file, "[%p] Memory free-up with \"delete\": file "
                      "\"%s\", function \"%s\", line %d.\n", memory, file_name.c_str(), func_name.c_str(), com_line);
    fclose(log_file);
    ::operator delete[](memory);
}

//! Just clears the log file (file name - macro LOG_FILE_NAME)
void clear_log()
{
    FILE* log_file = fopen(LOG_FILE_NAME, "w");
    fclose(log_file);
}

