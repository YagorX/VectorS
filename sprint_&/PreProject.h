#pragma once


/*
template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0): a_size_{a_size}
    {
        if (a_size > N)
            throw std::invalid_argument("Size more max_size");
    }

    T& operator[](size_t index) { return array_stack_[index]; }
    const T& operator[](size_t index) const { return array_stack_[index]; }

    auto begin() { return array_stack_.begin(); }
    auto end() { return array_stack_.end(); };
    auto begin() const { return array_stack_.begin(); }
    auto end() const { return array_stack_.end(); };
    size_t Size() const { return a_size_; }
    size_t Capacity() const { return N; }

    void PushBack(const T& value)
    {
        if (a_size_ > N - 1)
            throw std::overflow_error("if push_back, you more max_Size");
        array_stack_[a_size_] = value;
        a_size_++;
    }
    T PopBack()
    {
        if (a_size_ == 0)
            throw std::underflow_error("Pop empty vector");
        array_stack_[a_size_ - 1] = 0;
        a_size_--;
    }
private:
    size_t a_size_;
    std::array<T, N> array_stack_;
};


int main()
{
    StackVector<int, 5> stack_v{};

    return 0;
}
*/

/*
std::vector<std::string_view> SplitIntoWordsView(std::string_view str) {
    std::vector<std::string_view> result;
    const int64_t pos_end = str.npos;
    while (true) {
        int64_t space = str.find(' ');
        result.push_back(space == pos_end ? str.substr(0) : str.substr(0, space));
        if (space == pos_end) {
            break;
        }
        else {
            str.remove_prefix(space+1);
        }
    }

    return result;
}

int main()
{
    std::string str{ "Hello World Egor Lox!!" };
    auto result = SplitIntoWordsView(str);
    std::cout << str;
    std::cout << result[0];
    return 0;
}
*/

/*

class Translator {
public:
    void Add(std::string_view source, std::string_view target)
    {
        std::string sour{ source };
        std::string targ{ target };
        map_back.insert(std::pair(sour, targ));
        map_forw.insert(std::pair(targ, sour));
    }
    std::string TranslateForward(std::string_view source) const
    {
        try {
            std::string sour{ source };
            return map_back.at(sour);
        }
        catch(std::out_of_range){
            return "";
        }
    }
    std::string TranslateBackward(std::string_view target) const
    {

        auto res = map_back.find("window");
        try {
            std::string targ{ target };
            return map_back.at(targ);
        }
        catch (std::out_of_range) {
            return "";
        }

    }

private:
    std::map<std::string, std::string> map_forw;
    std::map<std::string, std::string> map_back;
};

void TestSimple() {
    Translator translator;
    translator.Add(std::string("okno"), std::string("window"));
    translator.Add(std::string("stol"), std::string("table"));

    assert(translator.TranslateForward("okno"s) == "window"s);
    assert(translator.TranslateBackward("table"s) == "stol"s);
    assert(translator.TranslateForward("table"s) == ""s);
}

int main() {
    TestSimple();
    return 0;
}
*/

