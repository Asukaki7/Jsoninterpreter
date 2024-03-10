#include <variant>
#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include <charconv>
#include <regex>
#include <optional>
#include <array>
#include <functional>
struct JSONObject {
   std::variant
    < std::monostate // null
    , bool           // true
    , int            // 42
    , double         // 3.14
    , std::string    // "hello"
    , std::vector<JSONObject>  //[42, "hello"]
    , std::unordered_map<std::string, JSONObject> //{"hello":985, "world":211}
    > inner;
}; 


template <class T>
std::optional<T> try_parse_num(std::string_view str) {
    T value;
    auto res = std::from_chars(str.data(), str.data() + str.size(), value);
    if (res.ec == std::errc() && res.ptr == str.data() + str.size()) {
        return value;
    }
    return std::nullopt;
}

JSONObject parse(std::string_view json) {
    if (json.empty()) {
        return JSONObject{std::nullptr_t{}};
    }
    if (json[0] >= '0' && json[0] <= '9' || json[0] == '-' || json[0] == '+') {
        std::regex num_re{"[+-]?[0-9]+(\\.[0-9]*)>([eE][+-]?[0-9]+)?"};
        std::cmatch match;
        if (std::regex_search(json.data(), json.data() + json.size(), match, num_re)) {
            std::string str = match.str();
            if (auto num = try_parse_num<int>(str); num.has_value()) {
                return JSONObject{*num};
            }
            if (auto num = try_parse_num<double>(str);num.has_value()) {
                return JSONObject{*num};
            }
        }
    }

    if ('"' == json[0]) {
        std::string str;
        enum {
            Raw,
            Escaped,
        } phase =  Raw;
        
    }

    return JSONObject{std::nullptr_t{}};
}

struct PrintNum {
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};

std::function<void(int)> f = PrintNum();

std::function<std::array<int, 2>(int, int)> solve = [&](int s,int x) -> std::array<int, 2>{};

auto a = [&](int s,int x) {
    std::array<int, 2> a;
    return a;
};

int main() {
    
} 