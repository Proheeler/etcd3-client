#include "Client.hpp"
#include "Condition.hpp"
#include "Request.hpp"

int main() {

    Client oClient("localhost:2379");

    std::pair <std::string, std::string> pair;
    
    oClient.put("NewKey", "etcd!!");
    //oClient.put("foo1", "bar1");
    //oClient.put("foo2", "bar2");
    //oClient.put("foo3", "bar3");
    //oClient.put("foo3", "bar3", pair);
    //std::cout << "foo3 previous[key:value]: "<< pair.first << ":"<< pair.second << std::endl; 
    //std::cout << oClient.get("Hallo") <<std::endl;
   
     std::map<std::string, std::string>  res1, res2;
    std::vector<std::string> res3;
    
    //oClient.getFromKey("foo1", res1);
    //std::cout << "===================================="<<std::endl; 
    //for(auto item: res1){ std::cout << item.first << ":" << item.second << std::endl; }
    //std::cout << "===================================="<<std::endl; 
    
    //oClient.get("foo", res2);
    //for(auto item: res2){ std::cout << item.first << ":" << item.second << std::endl; }
    //std::cout << "===================================="<<std::endl; 
    
    //oClient.getKeys("foo", res3);
    //for(auto item: res3){ std::cout << item << std::endl; }
    //std::cout << "===================================="<<std::endl; 

    //Status s = oClient.txn("foo", "There6");
    //if(s.ok()){
    //    std::cerr << "ok" << s.error_code() << ":" << s.error_message() << std::endl;
    //} else {
    //    std::cerr << s.error_code() << ":" << s.error_message() << std::endl;
  // }

    //oClient.watch("NewKey", 
    //    [](auto event){ std::cout << "Rcvd:" << event.type()  << ":" 
    //                                                          << event.kv().key() << "-"
    //                                                          << event.kv().value() 
    //                                                          << std::endl;
    //   } 
    //);
     
    std::list<Request> sreqs;
    std::list<Request> freqs;
    std::list<Condition> conditions;

    Condition con1("create", "foo", "There6");
    //Condition con2("mod", ">", "key2", "0");
    conditions.push_back(con1);
    //conditions.push_back(con2);

    Request req1("get", "foo3", "value1");
    Request req2("get", "foo2", "value1");
    Request req3("put", "newfoo1", "value1");

    sreqs.push_back(req1);
    sreqs.push_back(req2);
    sreqs.push_back(req3);
    freqs.push_back(req1);


    Status s = oClient.transaction(conditions, sreqs, freqs); 
    if(s.ok()){
        std::cerr << "ok" << s.error_code() << ":" << s.error_message() << std::endl;
    } else {
        std::cerr << s.error_code() << ":" << s.error_message() << std::endl;
    }
    
    // Getting the responses through a callback 
    oClient.transaction(conditions, sreqs, freqs, [](auto r) {
        for(auto resp: r.responses()){
           for(auto kvs_items: resp.response_range().kvs()){
                std::cerr << kvs_items.key() << 
                      ":" << kvs_items.value() << std::endl;
            }                
        }
    }); 
}
