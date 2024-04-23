Rebol [
    title: "Rebol/Template extension CI test"
]

print ["Running test on Rebol build:" mold to-block system/build]

;; make sure that we load a fresh extension
try [system/modules/template: none]
;; use current directory as a modules location
system/options/modules: what-dir

;; import the extension
test-module: import 'template

print as-yellow "Content of the module..."
? test-module
