#pragma once
#include <vector>   // for std::vector
#include <string>   // for std::string
#include <sstream>  // for std::stringstream


#include "xEmutex.h"

namespace SEABASE {

    class xStringUtil {
    public:
        /**
         * @brief toupper_inplace ��C����ַ���strת��Ϊ��д��ԭ�ַ�������д
         *
         * @param str ��ת����C����ַ���
         */
        static void toupper_inplace(char* str);

        /**
         * @brief toupper ��C����ַ���strת��Ϊ��д��ԭ�ַ������ֲ���
         *
         * @param str ��ת����C����ַ���
         *
         * @return �ַ���str�Ĵ�д��ʽ
         */
        static std::string toupper(const char* str);

        /**
         * @brief toupper ���ַ���strת��Ϊ��д��ԭ�ַ������ֲ���
         *
         * @param str ��ת�����ַ���
         *
         * @return �ַ���str�Ĵ�д��ʽ
         */
        static std::string toupper(const std::string& str);

        /**
         * @brief tolower_inplace ��C����ַ���strת��ΪСд��ԭ�ַ�������д
         *
         * @param str ��ת����C����ַ���
         */
        static void tolower_inplace(char* str);

        /**
         * @brief tolower ��C����ַ���strת��ΪСд��ԭ�ַ������ֲ���
         *
         * @param str ��ת����C����ַ���
         *
         * @return �ַ���str��Сд��ʽ
         */
        static std::string tolower(const char* str);

        /**
         * @brief tolower ���ַ���strת��ΪСд��ԭ�ַ������ֲ���
         *
         * @param str ��ת�����ַ���
         *
         * @return �ַ���str��Сд��ʽ
         */
        static std::string tolower(const std::string& str);

        /**
         * @brief ltrim_inplace ȥ���ַ�����˵Ŀհף�ԭ���޸�
         *
         * @param str ԭ�ַ���
         */
        static void ltrim_inplace(char* str);

        /**
         * @brief ltrim ȥ���ַ�����˵Ŀհף�ԭ�ַ������ֲ���
         *
         * @param str ԭ�ַ���
         *
         * @return ȥ����˿հ׵��ַ���
         */
        static std::string ltrim(const char* str);

        /**
         * @brief ltrim ȥ���ַ�����˵Ŀհף�ԭ�ַ������ֲ���
         *
         * @param str ԭ�ַ���
         *
         * @return ȥ����˿հ׵��ַ���
         */
        static std::string ltrim(const std::string& str);

        /**
         * @brief rtrim_inplace ȥ���ַ����Ҷ˵Ŀհף�ԭ���޸�
         *
         * @param str ԭ�ַ���
         */
        static void rtrim_inplace(char* str);

        /**
         * @brief rtrim ȥ���ַ����Ҷ˵Ŀհ�
         *
         * @param str ԭ�ַ���
         *
         * @return ȥ���Ҷ˿հ׵��ַ���
         */
        static std::string rtrim(const char* str);

        /**
         * @brief rtrim ȥ���ַ����Ҷ˵Ŀհ�
         *
         * @param str ԭ�ַ���
         *
         * @return ȥ���Ҷ˿հ׵��ַ���
         */
        static std::string rtrim(const std::string& str);

        /**
         * @brief trim_inplace ȥ��C����ַ������˿հף�ԭ���޸�
         *
         * @param str ԭ�ַ���
         */
        static void trim_inplace(char* str);

        /**
         * @brief trim ȥ��C����ַ������˿հ�
         *
         * @param str ԭ�ַ���
         *
         * @return ȥ�����˿հ׵��ַ���
         */
        static std::string trim(const char* str);

        /**
         * @brief trim ȥ���ַ������˿հ�
         *
         * @param str ԭ�ַ���
         *
         * @return  ȥ�����˿հ׵��ַ���
         */
        static std::string trim(const std::string& str);

        /**
         * @brief split_string �з��Ӵ�
         *
         * @param str ԭ�ַ���
         * @param separator �ָ���
         * @param container �Ӵ����
         * @param filter_empty �Ƿ���˿��Ӵ�(length == 0)
         */
        static void split_string(const std::string& str, const std::string& separator,
                std::vector<std::string>& container, bool filter_empty = false);

        /**
         * @brief replace_string �滻�Ӵ�
         *
         * @param str ԭ�ַ���
         * @param target Ŀ�괮
         * @param replacement �滻��
         *
         * @return �滻��ɺ���ַ���
         */
        static std::string replace_string(const std::string& str, const std::string& target,
                const std::string& replacement);

        /**
         * @brief str2uint32 �������ַ���ת��Ϊ32λ�޷�������
         *
         * @param str �����ַ���
         * @param number �������
         *
         * @return true��ʾת���ɹ������򷵻�false
         */
        static bool str2uint32(const char* str, uint32_t& number);

        /**
         * @brief str2int32 �������ַ���ת��Ϊ32λ�з�������
         *
         * @param str �����ַ���
         * @param number �������
         *
         * @return true��ʾת���ɹ������򷵻�false
         */
        static bool str2int32(const char* str, int32_t& number);

        /**
         * @brief str2uint64 �������ַ���ת��Ϊ64λ�޷�������
         *
         * @param str �����ַ���
         * @param number �������
         *
         * @return true��ʾת���ɹ������򷵻�false
         */
        static bool str2uint64(const char* str, uint64_t& number);

        /**
         * @brief str2int64 �������ַ���ת��Ϊ64λ�з�������
         *
         * @param str �����ַ���
         * @param number �������
         *
         * @return true��ʾת���ɹ������򷵻�false
         */
        static bool str2int64(const char* str, int64_t& number);

        /**
         * @brief generate_uuid ����uuid
         *
         * @return ���ء�1b4e28ba-2fa1-11d2-883f-b9a76����ʽ��uuid�ַ���
         */
        static std::string generate_uuid();

        /**
         * @brief ipv4_ntoa ����ip��ַת��Ϊ�ַ�����ʽ
         *
         * @param src ����IP
         * @param dest �����ַ�����ʽ��IP
         *
         * @return �ɹ�ת������true�����򷵻�false
         */
        static bool ipv4_ntoa(uint32_t src, std::string& dest);

        /**
         * @brief ipv4_aton �ַ���IP��ַת��Ϊ����
         *
         * @param src �ַ�����ʽ��IP
         * @param dest ����IP
         *
         * @return �ɹ�ת������true�����򷵻�false
         */
        static bool ipv4_aton(const char* src, uint32_t& dest);

        /**
         * @brief xstrncpy ����ͬstrncpy����������xstrncpy����ֵΪ�ɹ����Ƶ��ֽ���
         *
         * @param dest Ŀ�Ļ�����
         * @param src Դ�ַ���
         * @param n Ŀ�Ļ�������С
         *
         * @return �ɹ����Ƶ��ֽ���������ʱ����-1
         */
        static int32_t xstrncpy(char* dest, const char* src, int32_t n);

        /**
         * @brief rand_string ȡ��һ����������ַ�����ʽ
         *
         * @return ������ַ���
         */
        static std::string rand_string();

        /**
         * @brief str2integer �������ַ���ת����ΪT�͵�����
         *
         * @tparam T ��������
         * @param str C����ַ���
         * @param number �������
         *
         * @return �ɹ�����true�����򷵻�false
         */
        template <typename T>
            static bool str2integer(const char* str, T& number) {
                if (NULL == str) {
                    return false;
                }

                std::stringstream ss;
                T tmp;
                bool ret = false;

                ss << xStringUtil::trim(str);
                if (ss.str().length() > 0) {
                    try {
                        ss >> tmp;
                        if (ss.eof() && !ss.fail()) {
                            ret = true;
                            number = tmp;
                        }
                    }
                    catch(std::ios_base::failure& ) {
                    }
                }

                return ret;
            }

        template <typename T>
        static std::string integer2str(const T& number) {
            std::stringstream ss;
            ss << number;
            return ss.str();
        }
    private:
        /**
         * @brief rtrim ȥ���ַ����Ҷ˿հ�
         *
         * @param str C����ַ���
         * @param len C����ַ�������
         *
         * @return ȥ���Ҷ˿հ׵��ַ���
         */
        static std::string rtrim(const char* str, int32_t len);
		static xEmutex stMutex;
    }; // end of class StringUtil

}



