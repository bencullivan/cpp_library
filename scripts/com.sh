export cpp_library_cc_flags="-O2 -Wall -D NOT_ONLINE_JUDGE=1 -D LOCAL=1 -D BCDBG=1 -include $cpp_library_path/templates/dbg.h -I$ac_library_path"
function com_version() {
	g++-11 -std=gnu++$2 $cpp_library_cc_flags $1".cc"
}
function com() {
	com_version $1 17
	./a.out
}
function com14() {
	com_version $1 14
	./a.out
}
function com11() {
	com_version $1 11
	./a.out
}
function go() {
	if [ "$#" -eq 0 ]; then
		grep -v "dbg(\|dba(" a.cc > sol.cc
	else
		grep -v "dbg(\|dba(" "$1".cc > sol.cc
	fi
}
function show_graph() {
	python3 $cpp_library_path/scripts/show_graph.py < "$1.txt"
}
function show_digraph() {
	python3 $cpp_library_path/scripts/show_digraph.py < "$1.txt"
}
function show_weighted_graph() {
	python3 $cpp_library_path/scripts/show_weighted_graph.py < "$1.txt"
}
function show_weighted_digraph() {
	python3 $cpp_library_path/scripts/show_weighted_digraph.py < "$1.txt"
}
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
function get() {
	python3 $cpp_library_path/scripts/get.py $(pwd) $@
}