#include "codeclean.h"

using std::string;
using std::array;

using com::goffersoft::codeclean::codeclean;
using com::goffersoft::codeclean::testsuite;
using com::goffersoft::codeclean::testcase;
using com::goffersoft::codeclean::test;

uint32_t testcase::next_id = 1;
uint32_t testsuite::next_id = 1;
uint32_t test::next_id = 1;

const string&  test::noname = "t-noname";
const string&  testcase::noname = "tc-noname";
const string&  testsuite::noname = "ts-noname";


const string codeclean::ws_prefix = string(0, ' ');
const string testsuite::ws_prefix = string(4, ' ');
const string testcase::ws_tc_prefix = string(8, ' ');
const string testcase::ws_t_prefix = string(12, ' ');
const string test::ws_ts_prefix = string(16, ' ');
const string test::ws_r_prefix = string(20, ' ');
        
const array<const char*, 256>&
test::escs = test::init_escs();

template<>
string* test::get_raw<string>(const string& oldstr) {
    string *newstr = new string;
    for(auto c : oldstr) {
        if(escs[c] != nullptr) {
            *newstr += escs[c];
        } else {
            *newstr += c;
        }
    }
    return newstr;
}
