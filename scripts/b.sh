function gen() {
    for f in "$@"; do
        cp $cpp_library_path/templates/template.cc ./"$f".cc
    done
}
function ngen() {
    for f in "$@"; do
        cp $cpp_library_path/templates/template_no_cases.cc ./"$f".cc
    done
}
function ggen() {
    for f in "$@"; do
        cp $cpp_library_path/templates/google.cc ./"$f".cc
    done
}