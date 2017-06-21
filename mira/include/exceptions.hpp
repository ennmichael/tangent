#include <exception>

namespace Tangent {
namespace Mira {

namespace User_errors {

class Base_exception : public std::exception {
  // TODO
};

class Function_doesnt_exist : public Base_exception {
  // TODO
};

class Incorrect_number_of_parameter_values : public Base_exception {
  // TODO
};

}

namespace Internal_errors {



}

}
}
