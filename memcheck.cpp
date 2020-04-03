#include <iostream>

#define NEW new(__FILE__, __PRETTY_FUNCTION__, __LINE__)
#define DELETE(memory) operator delete (memory, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define DELETE_(memory) operator delete[](memory, __FILE__, __PRETTY_FUNCTION__, __LINE__)

void* operator new(size_t size, const std::string& file_name, const std::string& func_name, int com_line)
{
    FILE* log_file = nullptr;
    void* memory = nullptr;

    log_file = freopen("memory.log", "a", stdout);

    memory = ::operator new(size);

    std::cout << "[" << memory << "] Memory allocating with \"new\": file "
                                  "\"" << file_name << "\", function \"" << func_name <<"\", line " << com_line << ", size " << size <<"." << std::endl;
    fclose(log_file);

    return memory;
}

void * operator new[](size_t size, const std::string& file_name, const std::string& func_name, int com_line)
{
    FILE* log_file = nullptr;
    void* memory = nullptr;

    log_file = freopen("memory.log", "a", stdout);

    memory = ::operator new[](size);

    std::cout << "[" << memory << "] Memory allocating with \"new[]\": file "
                                  "\"" << file_name << "\", function \"" << func_name <<"\", line " << com_line << ", size " << size << "." << std::endl;
    fclose(log_file);

    return memory;
}

void operator delete(void* memory, const std::string& file_name, const std::string& func_name, int com_line)
{
    FILE* log_file = nullptr;

    log_file = freopen("memory.log", "a", stdout);

    std::cout << "[" << memory << "] Memory free-up with \"delete\": file "
                                  "\"" << file_name << "\", function \"" << func_name <<"\", line " << com_line << "." << std::endl;

    fclose(log_file);
    ::operator delete(memory);
}

void operator delete[](void* memory, const std::string& file_name, const std::string& func_name, int com_line)
{
    FILE* log_file = nullptr;

    log_file = freopen("memory.log", "a", stdout);

    std::cout << "[" << memory << "] Memory free-up with \"delete[]\": file "
                                  "\"" << file_name << "\", function \"" << func_name <<"\", line " << com_line << "." << std::endl;
    fclose(log_file);
    ::operator delete[](memory);
}

int special_num(int num)
{
    int counter = 0;
    int result = 0;
    int* arr = nullptr;

    arr = NEW int[num];
    arr[0] = 1;

    for (counter = 1; counter < num; counter++)
    {
        arr[counter] = counter * arr[counter - 1];
    }

    result = arr[num - 1];
    DELETE_(arr);

    return result;

}

int main() {
    int* x = nullptr;
    x = NEW int;
    std::cin >> *x;
    std::cout << special_num(*x);

    DELETE(x);
    return 0;
}
