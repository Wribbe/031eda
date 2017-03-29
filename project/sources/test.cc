#include <iostream>
#include <map>
void f_com_list_ng() 
{
  std::cout << "Hello from: COM_LIST_NG" << std::endl;
}

void f_com_create_ng() 
{
  std::cout << "Hello from: COM_CREATE_NG" << std::endl;
}

void f_com_delete_ng() 
{
  std::cout << "Hello from: COM_DELETE_NG" << std::endl;
}

void f_com_list_art() 
{
  std::cout << "Hello from: COM_LIST_ART" << std::endl;
}

void f_com_create_art() 
{
  std::cout << "Hello from: COM_CREATE_ART" << std::endl;
}

void f_com_delete_art() 
{
  std::cout << "Hello from: COM_DELETE_ART" << std::endl;
}

void f_com_get_art() 
{
  std::cout << "Hello from: COM_GET_ART" << std::endl;
}

void f_com_end() 
{
  std::cout << "Hello from: COM_END" << std::endl;
}

void f_ans_list_ng() 
{
  std::cout << "Hello from: ANS_LIST_NG" << std::endl;
}

void f_ans_create_ng() 
{
  std::cout << "Hello from: ANS_CREATE_NG" << std::endl;
}

void f_ans_delete_ng() 
{
  std::cout << "Hello from: ANS_DELETE_NG" << std::endl;
}

void f_ans_list_art() 
{
  std::cout << "Hello from: ANS_LIST_ART" << std::endl;
}

void f_ans_create_art() 
{
  std::cout << "Hello from: ANS_CREATE_ART" << std::endl;
}

void f_ans_delete_art() 
{
  std::cout << "Hello from: ANS_DELETE_ART" << std::endl;
}

void f_ans_get_art() 
{
  std::cout << "Hello from: ANS_GET_ART" << std::endl;
}

void f_ans_end() 
{
  std::cout << "Hello from: ANS_END" << std::endl;
}

void f_ans_ack() 
{
  std::cout << "Hello from: ANS_ACK" << std::endl;
}

void f_ans_nak() 
{
  std::cout << "Hello from: ANS_NAK" << std::endl;
}

void f_par_string() 
{
  std::cout << "Hello from: PAR_STRING" << std::endl;
}

void f_par_num() 
{
  std::cout << "Hello from: PAR_NUM" << std::endl;
}

void f_err_ng_already_exists() 
{
  std::cout << "Hello from: ERR_NG_ALREADY_EXISTS" << std::endl;
}

void f_err_ng_does_not_exist() 
{
  std::cout << "Hello from: ERR_NG_DOES_NOT_EXIST" << std::endl;
}

void f_err_art_does_not_exist() 
{
  std::cout << "Hello from: ERR_ART_DOES_NOT_EXIST" << std::endl;
}

int main(int argc, char ** argv)
{
  std::map<std::string,void (*) (void)> func_map;
  func_map.emplace("ANS_ACK",f_ans_ack);
  func_map.emplace("ANS_CREATE_ART",f_ans_create_art);
  func_map.emplace("ANS_CREATE_NG",f_ans_create_ng);
  func_map.emplace("ANS_DELETE_ART",f_ans_delete_art);
  func_map.emplace("ANS_DELETE_NG",f_ans_delete_ng);
  func_map.emplace("ANS_END",f_ans_end);
  func_map.emplace("ANS_GET_ART",f_ans_get_art);
  func_map.emplace("ANS_LIST_ART",f_ans_list_art);
  func_map.emplace("ANS_LIST_NG",f_ans_list_ng);
  func_map.emplace("ANS_NAK",f_ans_nak);
  func_map.emplace("COM_CREATE_ART",f_com_create_art);
  func_map.emplace("COM_CREATE_NG",f_com_create_ng);
  func_map.emplace("COM_DELETE_ART",f_com_delete_art);
  func_map.emplace("COM_DELETE_NG",f_com_delete_ng);
  func_map.emplace("COM_END",f_com_end);
  func_map.emplace("COM_GET_ART",f_com_get_art);
  func_map.emplace("COM_LIST_ART",f_com_list_art);
  func_map.emplace("COM_LIST_NG",f_com_list_ng);
  func_map.emplace("ERR_ART_DOES_NOT_EXIST",f_err_art_does_not_exist);
  func_map.emplace("ERR_NG_ALREADY_EXISTS",f_err_ng_already_exists);
  func_map.emplace("ERR_NG_DOES_NOT_EXIST",f_err_ng_does_not_exist);
  func_map.emplace("PAR_NUM",f_par_num);
  func_map.emplace("PAR_STRING",f_par_string);
  std::string token_name;
  std::cout << "Enter a protocol token:" << std::endl;
  while(std::cin >> token_name) {
      auto pointer = func_map.find(token_name);
      if (pointer == func_map.end()) {
          std::cout << "Don't know what to do about: " << token_name << ", try another." << std::endl;
      } else {
          (*pointer).second();
      }
  }
}
