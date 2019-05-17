// pugixmltest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "../../base/pugixml/include/pugixml.hpp"
#pragma comment(lib,"../../base/pugixml/lib/windows/debug/pugixml.lib")
 using namespace pugi;
using namespace std;
int main()
{
	pugi::xml_document doc;
	if(!doc.load_file("alisdk.xml",parse_full, encoding_utf8))
		return 0 ;
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
	return 0;
}

