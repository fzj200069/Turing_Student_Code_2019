#include<iostream>
#include<cstring>
#include<string>
#include<regex>
#include<fstream>
#include<sstream>
#include<ios>
#include<set>
#include<queue>
#include"total.h"
int main ()
{
	std::set <std::string> str_set;
	std::pair<std::set<std::string>::iterator,bool>ret;
	std::queue <std::string> str_queue; 
    //system ("wget info.ruc.edu.cn -O ./home1/.html -T 20 -q");
    str_set.insert(" "); 
    str_set.insert("http://info.ruc.edu.cn");
    str_queue.push("http://info.ruc.edu.cn");
    int ans = 0;
	while(!str_queue.empty())
	{
		std::string wget_str;
		std::string str;
		ans++;
		//const char* str_que=str_queue.front().data();
		//sprintf(wget_str,"wget %s -O ./home/%d.html -T 20 -q",str_que,ans);
		wget_str="wget "+str_queue.front()+" -O ./home/"+std::to_string(ans)+".html -t 3 -T 15 -q";
		system(wget_str.c_str());
		std::cout<<ans<<' '<<str_queue.front()<<std::endl;
		str_queue.pop();
		//sprintf(str,"./home/%d.html",ans);
		str="./home/"+std::to_string(ans)+".html";
		std::ifstream cur_url (str.c_str());
    	        std::string col;
    	        std::string full_url;
   		std::string mini_url;
		while(getline(cur_url,col))
    	{
			std::regex url_regex("(%*href=\")([^\"]*)");
	   		std::smatch res;
  			while(std::regex_search(col,res,url_regex))
    		{
    			full_url=" "; 
    			mini_url=res[2].str();								
    			if(format_bool(mini_url)&&url_bool(mini_url))
		    		full_url=minitofull(mini_url);
	    		ret=str_set.insert(full_url);
	    		if(ret.second!=false)
		    		str_queue.push(full_url);
  	    		col=res.suffix();
    		}
    	}  	
	}
	std::cout<<ans<<std::endl;
    return 0;
}
