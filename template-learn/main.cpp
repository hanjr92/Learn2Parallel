#include<iostream>

template<typename T = int> // template 模板避免重复代码, 可以指定默认类型
T twice(T t)
{
    return t * 2;
}


template<int N, typename T> // int N 默认参数仅能为整数类型,编译期常量会进行编译优化，可以在编译unroll循环
// func(int N) 是运行时常量，不会再编译期优化。 模板的使用会让编译文件变大
void showtime(T t)
{
    for(int i = 0; i < N; i++)
        std::cout << t << std::endl;
}

std::string twice(const std::string & t) //特殊情况会自动与现有模板互相重载
{
    return t + t;
}


// 模板的应用，编译期优化
template<bool debug> // 编译器会生成两份函数，前者保留打印信息，后者去除，这样就能达到运行时的优化。
int sum(int n)
// int sum(int n, bool debug) //如果将debug放入函数参数，则在编译不优化掉debug的判断，尽管debug可能是false
{
    int res = 0;
    for (int i=1; i<n; i++)
    {
        res += i;
        if constexpr (debug) // constexpr 关键词保证编译时判断，判断的变量不能使用运行时变量
        {
            std::cout << i << "-th: "<< res << std::endl;
        }
    }
    return res;
}

int main()
{
    std::cout << twice(21) << std::endl;
    std::cout << twice(2.1f) << std::endl;
    std::cout << twice(2.1) << std::endl;
    std::cout << twice<double>(2.1) << std::endl; // 指定模板类型
    std::cout << twice(std::string("hello!")) << std::endl;

    showtime<5>("five");


    constexpr bool debug = false; // debug必须为编译时常量
    std::cout << sum<debug>(5) << std::endl; 
    // std::cout << twice("hello!") << std::endl; // 不会自动将“hello！”转换为string 而是char类型，然后触发上面的模板
    return 0;
} 