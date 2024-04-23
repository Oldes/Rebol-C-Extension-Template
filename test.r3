Rebol [
	title: "Rebol/Template extension test"
]

print ["Running test on Rebol build:" mold to-block system/build]

;; make sure that we load a fresh extension
try [system/modules/template: none]

template: import template

? template

;; do some test with the extension

probe template/test

print "done"

