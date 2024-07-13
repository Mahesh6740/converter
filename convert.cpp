#include <iostream>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm> // Include this header for std::all_of

std::map<char, std::vector<std::string>> one_digit_words = {
    {'0', {"zero"}},
    {'1', {"one"}},
    {'2', {"two", "twen"}},
    {'3', {"three", "thir"}},
    {'4', {"four", "for"}},
    {'5', {"five", "fif"}},
    {'6', {"six"}},
    {'7', {"seven"}},
    {'8', {"eight"}},
    {'9', {"nine"}}
};

std::vector<std::string> two_digit_words = {"ten", "eleven", "twelve"};
std::string hundred = "hundred";
std::string thousand = "thousand";

std::string convertThreeDigitNumber(const std::string& num);

std::string convertNumber(const std::string& num) {
    std::string word;
    if (num == "0") {
        return "Zero";
    }
    if (num.length() == 4) {
        word += one_digit_words[num[0]][0] + " " + thousand;
        if (num.substr(1) != "000") {
            word += " ";
            word += convertThreeDigitNumber(num.substr(1));
        }
    } else {
        word += convertThreeDigitNumber(num);
    }
    word[0] = toupper(word[0]);
    return word;
}

std::string convertThreeDigitNumber(const std::string& num) {
    std::string word;
    std::string part = num;
    part.erase(0, std::min(part.find_first_not_of('0'), part.size()-1));

    if (part.length() == 1) {
        word += one_digit_words[part[0]][0];
    } else if (part.length() == 2) {
        if (part[0] == '1') {
            if (part[1] < '3') {
                word += two_digit_words[part[1] - '0'];
            } else {
                word += one_digit_words[part[1]][(part[1] >= '3' && part[1] <= '5' && (part[1] - '0') % 2 != 0) ? 1 : 0] +
                        ((part[1] == '8') ? "een" : "teen");
            }
        } else {
            word += one_digit_words[part[0]][part[0] == '2' ? 1 : 0] + ((part[0] == '8') ? "y" : "ty");
            if (part[1] != '0') {
                word += " " + one_digit_words[part[1]][0];
            }
        }
    } else if (part.length() == 3) {
        if (part[0] != '0') {
            word += one_digit_words[part[0]][0] + " " + hundred;
            if (part.substr(1) == "00") return word;
            word += " and ";
        }
        if (part[1] == '1') {
            if (part[2] < '3') {
                word += two_digit_words[part[2] - '0'];
            } else {
                word += one_digit_words[part[2]][(part[2] >= '3' && part[2] <= '5' && (part[2] - '0') % 2 != 0) ? 1 : 0] +
                        ((part[2] == '8') ? "een" : "teen");
            }
        } else {
            word += one_digit_words[part[1]][part[1] == '2' ? 1 : 0] + ((part[1] == '8') ? "y" : "ty");
            if (part[2] != '0') {
                word += " " + one_digit_words[part[2]][0];
            }
        }
    }
    return word;
}

int main() {
    std::string n;
    while (true) {
        std::cout << "Enter a number (0 to 9999) to convert it into words or 'exit' to stop: ";
        std::cin >> n;
        if (n == "exit") break;
        if (n.length() > 4 || !std::all_of(n.begin(), n.end(), ::isdigit)) {
            std::cout << "Error: Invalid Number! Please enter a number between 0 and 9999." << std::endl;
            continue;
        }
        std::cout << n << " --> " << convertNumber(n) << std::endl;
    }
    return 0;
}
