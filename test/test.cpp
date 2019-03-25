//
// Created by hhk on 18-12-17.
//
#include <bits/stdc++.h>
#include "ejson.h"
#pragma comment(lib, "libejson.a")

using std::cout;
using std::cin;
using std::endl;
using namespace EasyJson;

class AAAA{ };
void test_json() {
    JSONArray arr;
    JSONArray arr2;
    JSONObject obj;

    {
        // 测试1:使用 [] 来操作数组
        cout << "测试1: 使用[]来写数据 " << endl;
        JSONArray test1(2); // 初始化分配大小
        test1[0] = nullptr;
        test1[1] = "this is const char*";
        test1[2] = 12324.5;
        test1[5] = "中文字符串";
        test1[6] = AAAA();  // 故意加入错误数据查看是否可以输出,会自动忽略错误
        cout << test1 << endl;

        // 使用[] 操作对象
        JSONObject test2;
        test2["float"] = 123.456;
        test2["int"] = 24;
        test2["string"] = "this is a string";
        test2["array"] = test1;
        test2["nullptr"] = nullptr;
        cout << test2 << endl;
        cout << endl << endl;
    }

    {
        // vector<any> 初始化列表
        cout << "测试2: 使用add来写数据" << endl;
        const char *b = "特殊字符\"";
        vector<any> any_vec = {1, string("sdfa"), 123.4, string("skgja\"fas,d")};
        arr.add(3);
        arr.add(123.3);
        arr.add(b);
        arr.add("英文");
        arr.add(nullptr);
        arr.add(arr2); // 数组嵌套
        arr.add(any_vec); // 加入vector
        cout << arr << endl;
        cout << endl << endl;
    }

    {
        // add(<map<string, any>) 函数
        cout << "测试3" << endl;
        map<string, any> map_any;
        map_any["adsfdg"] = 123.4;
        const char *q = "asdfxv\"";
        map_any["fdsg,sdfjk"] = q;
        obj.add("123", arr);
        obj.add("name", "hhk\",sdfsdf");
        obj.add("df\"ag", q);
        obj.add(map_any); // 对象合并
        cout << obj << endl;
        cout << JSONObject(map_any) << endl; // map做构照函数
        cout << "格式化输出" << endl;
        cout << obj.toString(0) << endl;
        cout << endl << endl;
    }

    {
        // 测试解析字符串
        cout << "测试4 " << endl;
        // test parse arr
        string parse_str = "  [{},1, \"\", [  {}, {\"1\":2}],2.3, 4,null, [1, \"faskd,,f[[[]\\\" \", [2,3,\"dsafsf\", null], \"sadf 2\"], \"测试中文\"]";
        JSONBase *a = JSONBase::parse_arr(parse_str);
        cout << *a << endl;
        free(a);

        // test parse array
        parse_str = R"({"name" : "hhk" , "key1": "valu\"e1 ","key2":[1,2,"asd",{"sadf": 123, "sb": 12.3}, 123.3]})";
        a = JSONBase::parse_obj(parse_str);
        cout << *a << endl;
        free(a);

        // 带有缩进和回车
        string parse_str2;
        parse_str2 = "{\n"
                     "    \"123\": 132124,\n"
                     "    \"vasdfsss\": [\n"
                     "        1,\n"
                     "        2,\n"
                     "        \"fdsfsd\",\n"
                     "        {\n"
                     "            \"dsfdf\": 244\n"
                     "        }\n"
                     "    ],\n"
                     "    \"fsfsd\": 5245\n"
                     "}\n";
        //parse_str2 = "{\"123\": 132124, \"vasdfsss\": [1, 2, \"fdsfsd\", {\"dsfdf\": 244}], \"fsfsd\": 5245}";
        a = JSONBase::parse_obj(parse_str2);
        cout << *a << endl;
        free(a);
        cout << endl << endl;

        // 测试获取值的方法, 通用parse方法，返回JSONBase，可以转形
        cout << "测试5" << endl;
        auto *b = dynamic_cast<JSONObject *>(JSONBase::parse(parse_str));
        cout << b->get<string>("key1") << endl;
        cout << b->get<JSONArray>("key2").get<int>(1) << endl;
        free(b);
        cout << endl << endl;
    }
}

int main()
{
    test_json();
}