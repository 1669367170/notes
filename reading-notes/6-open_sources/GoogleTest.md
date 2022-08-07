# GoogleTest

官网使用说明指导：https://google.github.io/googletest/

github仓链接：https://github.com/google/googletest

## 一、介绍

![image-20220807152424640](C:\Users\16693\AppData\Roaming\Typora\typora-user-images\image-20220807152424640.png)

> - 测试应该是独立的和可重复的。调试由于其他测试而成功或失败的测试是一件痛苦的事。 googletest 通过在不同的对象上运行每个测试来隔离测试。当测试失败时，googletest 允许您单独运行它以进行快速调试。
> - 测试应该组织良好并反映测试代码的结构。 googletest 将相关测试分组到可以共享数据和子程序的测试套件中。这种常见的模式很容易识别并使测试易于维护。当人们切换项目并开始使用新的代码库时，这种一致性特别有用。
> - 测试应该是可移植的和可重复使用的。谷歌有很多平台中立的代码；它的测试也应该是平台中立的。 googletest 适用于不同的操作系统，使用不同的编译器，有或没有例外，因此 googletest 测试可以使用各种配置。
> - 当测试失败时，他们应该提供尽可能多的关于问题的信息。 googletest 不会在第一次测试失败时停止。相反，它只会停止当前测试并继续下一个测试。您还可以设置报告非致命故障的测试，然后当前测试继续。因此，您可以在单个运行-编辑-编译周期中检测和修复多个错误。
> - 测试框架应该将测试编写者从家务活中解放出来，让他们专注于测试内容。 googletest 自动跟踪定义的所有测试，并且不需要用户枚举它们以运行它们。
> - 测试应该很快。使用 googletest，您可以在测试之间重用共享资源，并且只需为设置/拆卸支付一次费用，而不会使测试相互依赖。

## 二、具体尝试-GoogleTest Primer

- Test(测试套件名，测试名)

### 1、Test Fixtures: Using the Same Data Configuration for Multiple Tests

> - 编写2个及以上使用相似数据进行操作的测试场景，创建一个fixtures
>
>   1）继承::testing::Test，protected开始类的主体；
>
>   2）在类中，声明计划使用的任何对象；
>
>   3）如有必要，编写默认构造函数或 SetUp() 函数来为每个测试准备对象；（注意SetUp拼写，可以使用override检查）
>
>   4）如有必要，编写析构函数或 TearDown() 函数来释放您在 SetUp() 中分配的任何资源。
>
>   5）如果需要，定义子程序供您的测试共享。
>
> ```C++
> TEST_F(TestFixtureName, TestName) {
>   ... test body ...
> }
> ```
>
> - 对于使用 TEST_F() 定义的每个测试，googletest 将在运行时创建一个新的测试Fixtures，立即通过 SetUp() 对其进行初始化，运行测试，通过调用 TearDown() 进行清理，然后删除该测试Fixtures。googletest 总是在创建下一个测试Fixtures之前删除一个测试Fixtures。 googletest 不会为多个测试重用相同的测试夹具

## 三、具体尝试-Advanced googletest Topics

### 1、更好的错误消息的谓语断言

> - 尽管 googletest 有一组丰富的断言，但不可能穷尽覆盖。有时用户必须使用 EXPECT_TRUE() 来检查复杂的表达式，因为缺少更好的宏。这样做的问题是没有向您显示表达式部分的值，因此很难理解出了什么问题。作为一种解决方法，一些用户选择自己构建失败消息，将其流式传输到 EXPECT_TRUE()。但是，这很尴尬，尤其是当表达式具有副作用或评估成本很高时。
>
> - googletest 提供了三种不同的选项来解决此问题：
>
>   1）使用现有的布尔函数 （参考EXPECT_PRED*）
>
>   2）使用返回 AssertionResult 的函数 （::testing::AssertionResult类）
>
>   3）使用谓词格式化程序 （如果发现 EXPECT_PRED* 和 EXPECT_TRUE 生成的默认消息不令人满意，或者谓词的某些参数不支持流式传输到 ostream，则可以改为使用谓词格式化程序断言来完全自定义消息的格式。 有关详细信息，请参阅断言参考中的 EXPECT_PRED_FORMAT*。）

### 2、浮点谓语格式函数

```C++
using ::testing::FloatLE;
using ::testing::DoubleLE;
...
EXPECT_PRED_FORMAT2(FloatLE, val1, val2);
EXPECT_PRED_FORMAT2(DoubleLE, val1, val2);
```

### 3、使用 gMock 匹配器断言

可以使用带有 EXPECT_THAT 的 gMock 字符串匹配器来执行更多字符串比较技巧（子字符串、前缀、后缀、正则表达式等）

```c++
using ::testing::HasSubstr;
using ::testing::MatchesRegex;
...
  ASSERT_THAT(foo_string, HasSubstr("needle"));
  EXPECT_THAT(bar_string, MatchesRegex("\\w*\\d+"));
```

### 4、类型断言

模板代码中常用

```c++
::testing::StaticAssertTypeEq<T1, T2>();

template <typename T> class Foo {
 public:
  void Bar() { testing::StaticAssertTypeEq<int, T>(); }
};
```

### 5、断言放置

### 6、跳过测试执行用例

```c++
TEST(SkipTest, DoesSkip) {
  GTEST_SKIP() << "Skipping single test";
  EXPECT_EQ(0, 1);  // Won't fail; it won't be executed
}

class SkipFixture : public ::testing::Test {
 protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

// Tests for SkipFixture won't be executed.
TEST_F(SkipFixture, SkipsOneTest) {
  EXPECT_EQ(5, 7);  // Won't fail
}
```

### 7、重定义流<<打印自定义类型

### 8、死亡测试

### 9、正则表达式语法

![image-20220807180205188](C:\Users\16693\AppData\Roaming\Typora\typora-user-images\image-20220807180205188.png)

> c 匹配任何文字字符 c
> \\d 匹配任何十进制数字
> \\D 匹配任何不是十进制数字的字符
> \\f 匹配 \f
> \\n 匹配 \n
> \\r 匹配 \r
> \\s 匹配任何 ASCII 空格，包括 \n
> \\S 匹配任何不是空格的字符
> \\t 匹配 \t
> \\v 匹配 \v
> \\w 匹配任何字母、_ 或十进制数字
> \\W 匹配任何 \\w 不匹配的字符
> \\c 匹配任何文字字符 c，它必须是标点符号
> . 匹配除 \n 之外的任何单个字符
> 一个？ 匹配 0 或 1 次出现的 A
> A* 匹配 0 次或多次出现的 A
> A+ 匹配 1 次或多次出现的 A
> ^ 匹配字符串的开头（不是每一行的开头）
> $ 匹配字符串的结尾（不是每一行的结尾）
> xy 匹配 x 后跟 y

### 10、死亡测试和线程

### 11、在子例程中使用断言

- SCOPED_TRACE

### 12、记录附加信息

- RecordProperty

### 13、Global Set-Up and Tear-Down

> - 测试级别（Test）、测试套件级别（Test Suite）、测试程序级别。gtest事件机制：testcase事件、testsuite事件、Global事件。
> - 怎么选择事件机制：1）setup、teardown内部调用时机；2）不同事件类的成员变量的生命周期。
>
> - 继承::testing::Environment 类来定义一个测试环境

### 14、值参数化测试

> 值参数化测试允许使用不同的参数测试您的代码，而无需编写同一测试的多个副本。 这在许多情况下都很有用。
>
> testing::TestWithParam<T>

### 15、类型化测试

> 假设有同一个接口的多个实现，并希望确保它们都满足一些共同的要求。 或者，可能已经定义了几个应该符合相同“概念”的类型，并且想要验证它。 在这两种情况下，都希望为不同类型重复相同的测试逻辑。

...