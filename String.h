#ifndef __DS_STRING__
    #define __DS_STRING__

    #include <stdlib.h>
    #include <cstring>
    #include <regex>

    using namespace std;

    class String{
        public:
            int length;

            String(){
                length = 0;
                value = NULL;
            }
            String(String &str){
                _String(&str[0]);
            }
            String(char str){
                string inp;

                inp += str;

                _String(inp.c_str());
            }
            String(const char* str){
                _String(str);
            }
            
            String operator+(String &str){
                return __add__(&str[0]);
            }
            String operator+(char str){
                string inp;

                inp += str;

                return __add__(inp.c_str());
            }
            String operator+(const char* str){
                return __add__(str);
            }
            
            String &operator+=(String &str){    
                __add_eq__(&str[0]);
                
                return (*this);
            }
            String &operator+=(char str){
                string inp;

                inp += str;

                __add_eq__(inp.c_str());

                return (*this);
            }
            String &operator+=(const char* str){
                __add_eq__(str);

                return (*this);
            }
            
            String &operator=(String &str){
                length = str.length;

                value = (char*)realloc(value,length * sizeof(char));
                
                for (int i = 0;i < length;i++)
                    value[i] = str[i];
                
                return (*this);
            }

            int* operator()(int i){
                return (int*)(value + i);
            }
            char &operator[](int i){
                return value[i];
            }

            String replace(char del,char str){
                String result((*this));

                for (int i = 0;i < result.length;i++)
                    if (result[i] == del){
                        result[i] = str;

                        break;
                    }

                return result;
            }
            String replace(const char* pattern,char str){
                regex reg(pattern);
                string sub;
                string result = &value[0];

                sub += str;

                result = regex_replace(result,reg,sub);

                return String(result.c_str());
            }

            ~String(){
                free(value);
            }
        
        private:
            char* value;

            void _String(const char* str){
                length = strlen(str);

                value = (char*)malloc(length * sizeof(char));

                if (value == NULL)
                    return;

                for (int i = 0;i < length;i++)
                    value[i] = str[i];
            }
            String __add__(const char* str){
                string result;

                for (int i = 0;i < strlen(str);i++)
                    result += str[i];
                
                return String(result.c_str());
            }
            void __add_eq__(const char* str){
                int diff = strlen(str);

                value = (char*)realloc(value,(length + diff) * sizeof(char));

                for (int i = 0;i < diff;i++)
                    value[length + i] = str[i];
                
                length += diff;
            }
    };

    string to_string(String &str){
        string result;

        for (int i = 0;i < str.length;i++)
            result += str[i];
        
        return result;
    }
#endif