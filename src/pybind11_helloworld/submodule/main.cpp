#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <type_traits>

namespace py = pybind11;

typedef std::int64_t datetime64_t;
static_assert(std::is_default_constructible<datetime64_t>::value, "datetime64_t is not default constructible");

namespace pybind11 {
namespace detail {

// Type conversion for numpy.datetime64 <--> datetime64_t
template <> struct type_caster<datetime64_t> {
public:
    PYBIND11_TYPE_CASTER(datetime64_t, _("numpy.datetime64"));

    bool load(handle src, bool) {
        static PyObject* astype_ptr = module::import("numpy").attr("datetime64").attr("astype").cast<object>().release().ptr();
        static PyObject* inttype_ptr = module::import("numpy").attr("int64").cast<object>().release().ptr();
        static PyObject* datetime_data_ptr = module::import("numpy").attr("datetime_data").cast<object>().release().ptr();

        object astype = reinterpret_borrow<object>(astype_ptr);
        object inttype = reinterpret_borrow<object>(inttype_ptr);
        object datetime_data_fn = reinterpret_borrow<object>(datetime_data_ptr);

        value = PyLong_AsLong(astype(src, inttype).ptr());
        auto datetime_data = datetime_data_fn(src).cast<std::tuple<std::string, int>>();
        const auto& base = std::get<0>(datetime_data);
        int step = std::get<1>(datetime_data);

        switch(base[1]) {
        case '\0':
            switch(base[0]) {
            case 'D':  // day
                value *= 24;
            case 'h':  // hour
                value *= 60;
            case 'm':  // minute
                value *= 60;
            case 's':  // second
                value *= 1000000000 * step;
                break;
            default:
                return false;
            }
            break;
        case 's':
            if (base[2] != '\0') {
                return false;
            }
            switch(base[0]) {
            case 'm':  // millisecond
                value *= 1000;
            case 'u':  // microsecond
                value *= 1000;
            case 'n':  // nanosecond
                value *= step;
                break;
            default:
                return false;
            }
            break;
        default:
            return false;
        }
        return true;
    }

    static handle cast(datetime64_t src, return_value_policy, handle) {
        // This line fails, it calls cast<>() recursively then segfaults
        static PyObject* datetime_ptr = module::import("numpy").attr("datetime64").cast<object>().release().ptr();
        object datetime = reinterpret_borrow<object>(datetime_ptr);
        return datetime(src, "ns");
    }
};

}} // namespace pybind11::detail


datetime64_t sometime() {
    return 1624905383956765909;
}

PYBIND11_MODULE(submodule, m) {
    m.doc() = "My docstring";
    m.def("sometime", &sometime, "A function that returns a np.datetime64");
}
