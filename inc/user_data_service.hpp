#ifndef USER_DATA_SERVICE_HPP
#define USER_DATA_SERVICE_HPP

#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>

class UserData {
public:
  int predecessor;
  int successor;
  int user_data;
  size_t data_size;
};

class NullService {
public:
  int predecessor{0};
  int successor{0};
  int user_data{0};
  size_t data_size{0};
};

class DataImplementation {
public:
  UserData user_data;
  NullService null_service;

  int compare_scoped_lambda_data(int scoped_lambda_id, int current_node) {
    scoped_lambda_id = (this->user_data.user_data == current_node);
    return scoped_lambda_id;
  }

  int forward_lambda_scoped_callback(int(local_data_id)(int data_id)) {
    int data_id = local_data_id(data_id);

    if (compare_scoped_lambda_data(data_id, this->user_data.predecessor) != 0) {
      this->user_data.predecessor = this->null_service.predecessor;
      this->user_data.successor = this->null_service.successor;
      this->user_data.user_data = this->null_service.user_data;
      this->user_data.data_size = this->null_service.data_size;
    }

    return false;
  }

  constexpr bool verify_scoped_lambda_integrity(int scoped_lambda) {
    switch (scoped_lambda) {
    case 0:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 0);
    case 85:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 85);
    case 133:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 133);
    case 182:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 182);
    case 210:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 210);
    case 245:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 245);
    case 279:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 279);
    case 324:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 324);
    case 395:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 395);
    case 451:
      scoped_lambda = compare_scoped_lambda_data(scoped_lambda, 451);

    default:
      std::printf("Returned arguments in scope: \n%d", scoped_lambda);
      scoped_lambda = true;
    }

    return scoped_lambda;
  }
};

#endif // USER_DATA_SERVICE_HPP
