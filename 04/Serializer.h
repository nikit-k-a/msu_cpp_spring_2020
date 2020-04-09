#ifndef SERIALIZER_H
#define SERIALIZER_H
#pragma once

enum class Error
{
    NoError,
    CorruptedArchive
};


class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <typename T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <typename... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

private:
    std::ostream& out_;

    Error print (bool val)
    {
        if (val) out_ << "true" << Separator;
        else if (!val) out_ << "false" << Separator;

        return Error::NoError;
    }

    Error print (uint64_t val)
    {
        out_  << val << Separator;
        return Error::NoError;
    }

    template <typename T>
    Error process(T val)
    {
        return print(val);
    }

    template <typename T, typename... Args>
    Error process(T val, Args... args)
    {
        Error error = print(val);

        if (error == Error::NoError)
        {
            return process(args...);
        }

        return error;
    }
};


class Deserializer
{
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <typename T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <typename... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }

private:
    std::istream& in_;

    bool is_number(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) it++;
        return (!s.empty()) && (it == s.end());
    }

    Error scan (bool& val)
    {
        std::string text;
        in_ >> text;

        if (text == "true")
        {
            val = true;
            return Error::NoError;
        }
        else if (text == "false")
        {
            val = false;
            return Error::NoError;
        }

        return Error::CorruptedArchive;
    }

    Error scan (uint64_t& val)
    {
        std::string text;
        in_ >> text;

        if (is_number(text))
        {
            int64_t v = std::stoi(text);
            val = v;
            return Error::NoError;
        }

        return Error::CorruptedArchive;
    }

    template <typename T>
    Error process (T& val)
    {
        return scan (val);
    }

    template <typename T, typename... Args>
    Error process(T& val, Args&... args)
    {
        Error error = scan (val);

        if (error == Error::NoError)
        {
            return process (args...);
        }

        return error;
    }
};

#endif //SERIALIZER_H
