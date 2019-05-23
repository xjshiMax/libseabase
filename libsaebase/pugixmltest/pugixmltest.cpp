// pugixmltest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include<list>
#include "../../base/pugixml/include/pugixml.hpp"
#pragma comment(lib,"../../base/pugixml/lib/windows/debug/pugixml.lib")
 using namespace pugi;
using namespace std;

static const char* kFileName = "students2.xml";

struct Student {
	int id;
	std::string name;
	int age;

	Student(int id_, const std::string& name_, int age_)
		: id(id_)
		, name(name_)
		, age(age_) {
	}

	void Print() const {
		std::cout << "Id: " << id << ", Name: " << name << ", Age: " << age << std::endl;
	}
};

// 创建XML。
static void WriteData() {
	// Prepare data.
	std::list<Student> students;
	students.push_back(Student(1, "MaZhe", 18));
	students.push_back(Student(2, "Miki", 19));
	students.push_back(Student(3, "Maki", 20));

	// Serialization.
	pugi::xml_document xdoc;

	pugi::xml_node xdec = xdoc.prepend_child(pugi::node_declaration);
	xdec.append_attribute("version").set_value("1.0");
	xdec.append_attribute("encoding").set_value("utf-8");

	pugi::xml_node xstudents = xdoc.append_child("Students");
	xstudents.append_child(pugi::node_comment).set_value("Students!");

	std::list<Student>::iterator ite=students.begin();
	while(ite!=students.end())
	{
		pugi::xml_node xstudent = xstudents.append_child("Student");

		pugi::xml_attribute xstudent_id = xstudent.append_attribute("id");
		xstudent_id.set_value(ite->id);

		pugi::xml_node xname = xstudent.append_child("Name");
		xname.append_child(pugi::node_pcdata).set_value(ite->name.c_str());

		pugi::xml_node xage = xstudent.append_child("Age");
		char buf[128] = { 0 };
		sprintf(buf, "%d", ite->age);
		xage.append_child(pugi::node_pcdata).set_value(buf);
		ite++;
	}

	xdoc.print(std::cout);

	xdoc.save_file(kFileName);
}
void Creategata(string name,string realm,string proxy,string expirese,string username,string password,string strregister)
{
	pugi::xml_document xdoc;
	pugi::xml_node xnode=xdoc.append_child("include");

	pugi::xml_node xgate = xnode.append_child("gateway");
	pugi::xml_attribute attname=xgate.append_attribute("name");
	attname.set_value(name.c_str());
	//xgata.append_attribute("name")=name;
	pugi::xml_node param1=xgate.append_child("param");
	pugi::xml_attribute name1=param1.append_attribute("name");
	name1.set_value("realm");
	pugi::xml_attribute value1=param1.append_attribute("value");
	value1.set_value(realm.c_str());

	pugi::xml_node param2=xgate.append_child("param");
	pugi::xml_attribute name2=param2.append_attribute("name");
	name2.set_value("proxy");
	pugi::xml_attribute value2=param2.append_attribute("value");
	value2.set_value(proxy.c_str());

	pugi::xml_node param3=xgate.append_child("param");
	pugi::xml_attribute name3=param3.append_attribute("name");
	name3.set_value("expire-seconds");
	pugi::xml_attribute value3=param3.append_attribute("value");
	value3.set_value(expirese.c_str());

	pugi::xml_node param4=xgate.append_child("param");
	pugi::xml_attribute name4=param4.append_attribute("name");
	name4.set_value("username");
	pugi::xml_attribute value4=param4.append_attribute("value");
	value4.set_value(username.c_str());

	pugi::xml_node param5=xgate.append_child("param");
	pugi::xml_attribute name5=param5.append_attribute("name");
	name5.set_value("password");
	pugi::xml_attribute value5=param5.append_attribute("value");
	value5.set_value(password.c_str());

	pugi::xml_node param6=xnode.append_child("param");
	pugi::xml_attribute name6=param6.append_attribute("name");
	name6.set_value("register");
	pugi::xml_attribute value6=param6.append_attribute("value");
	value6.set_value(strregister.c_str());
	xdoc.print(std::cout);
	string filename=name+".xml";
	xdoc.save_file(filename.c_str());

}


void loadxml()
{
	pugi::xml_document doc;
	if(!doc.load_file("alisdk.xml",parse_full, encoding_utf8))
		return  ;
	pugi::xml_node tools = doc.child("Profile").child("asrTools");
	for(pugi::xml_node count = tools.first_child();count;count=count.next_sibling())
	{
		// 		std::cout<<"Count:";
		// 		for(pugi::xml_attribute attr  = count.first_attribute();attr;attr=attr.next_attribute())
		// 		{
		// 			std::cout<<""<<attr.name()<<	"="<<attr.value();
		// 		}
		string appkey= count.attribute("appkey").as_string();
		if(appkey!="")
		{
			int o=0;
		}
	}
}

int main()
{
	//WriteData();
	Creategata("testgate","58.248.254.116:5060","58.248.254.116:5060","60","02022205303","12344321","true");
	return 0;
}

