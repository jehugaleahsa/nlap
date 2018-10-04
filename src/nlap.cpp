#include <napi.h>
#include <sstream>

#include <Eigen/Dense>


void console_log(Napi::Env env, std::initializer_list<napi_value> const& values) {
    using Napi::Function;

    auto console = env.Global().Get("console").ToObject();
    auto log = console.Get("log").As<Function>();
    log.Call(console, values);
}

void run(Napi::CallbackInfo const& callback) {
    using Eigen::Matrix;
    using Napi::String;
    using std::ostringstream;
    using std::string;

    auto A = Matrix<int, 2, 1>::Random();
    auto B = Matrix<int, 1, 2>::Random();
    auto C = A * B;

    ostringstream os;
    os << C;
    string output = os.str();

    auto env = callback.Env();
    console_log(env, { String::New(env, output) });
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
    using Napi::String;
    using Napi::Function;

    exports.Set(String::New(env, "run"), Function::New(env, run));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, init);