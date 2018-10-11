#ifndef ASSIGNMENT_4_OPERATORS_PROXY_TEST_H
#define ASSIGNMENT_4_OPERATORS_PROXY_TEST_H
#include <ostream>
class two_digs {
        private:
        //internal digits representation that saves space
        int m_digs;

        // a handy range checking function
        auto check(int value){
            return value > 0 && value < 10?
                   value :
                   throw std::out_of_range(std::to_string(value) + " is not a valid digit");
        }

        //private proxy class
        struct proxy{
            two_digs& m_owner;
            bool m_first;

            //helper function to extract the correct digit from the owner
            auto get_digit(bool first){return first? m_owner.m_digs / 10 : m_owner.m_digs - 10*(m_owner.m_digs / 10);}

            //type conversion to int (from proxy) - used to return the first or the second digit based on the m_first flag
            // notice that nested classes have access to the private fields of the owner
            operator int(){ return get_digit(m_first); };

            //assignment operator - used when a user assigns a new integer value to the proxy object
            proxy& operator=(int value){
                //check if in range
                value = m_owner.check(value);
                if (m_first){
                    auto second = get_digit(false);
                    m_owner.m_digs = value * 10 + second;
                }
                else{
                    auto first = get_digit(true);
                    m_owner.m_digs = value + first * 10;
                }
                return *this;
            }
        };
        public:
        // ctor
        two_digs(int first, int second):
        m_digs{ check(first) * 10 + check(10) }
        {}

        // returning a proxy
        proxy first(){
            return proxy{*this, true};
        }

        proxy second(){
            return proxy{*this, false};
        }
};


#endif //ASSIGNMENT_4_OPERATORS_PROXY_TEST_H
