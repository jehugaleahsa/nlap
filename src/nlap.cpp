#include <napi.h>
#include <sstream>

#include <Eigen/Dense>


Napi::String run(Napi::CallbackInfo const& callback) {
    using Eigen::MatrixXd;
    using std::ostringstream;

    MatrixXd matrix = MatrixXd::Random(2, 2);
    ostringstream os;
    os << matrix;

    auto env = callback.Env();
    return Napi::String::New(env, os.str());
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "run"), Napi::Function::New(env, run));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, init);