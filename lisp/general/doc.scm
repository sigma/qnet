(define-module (general doc))

(export defun
        defun*
        defvar
        documentation
        test-string)

(use-modules (ice-9 optargs))

(define documentation (make-object-property))
(set! (documentation 'documentation) "self documentation system")

(define (test-string e)
  (catch '#t (lambda () (string? e)) (lambda (key . args) nil)))
(set! (documentation 'test-string) "test if an expression is a string")

(defmacro* defun (name args docstring #:rest body)
  `(let ((decl (cons ',name ',args))
         (b ',body)
         (d ',docstring))
     (if (not (test-string ',docstring))
         (begin
           (set! b (cons ',docstring ',body))
           (set! d "undocumented")))
     (primitive-eval
      (list 'begin
            (append (list 'define decl) b)
            (list 'set! (list 'documentation (quote ',name)) d)))))
(set! (documentation 'defun) "define a function in emacs style")

(defmacro* defun* (name args docstring #:rest body)
  `(let ((decl (cons ',name ',args))
         (b ',body)
         (d ',docstring))
     (if (not (test-string ',docstring))
         (begin
           (set! b (cons ',docstring ',body))
           (set! d "undocumented")))
     (primitive-eval
      (list 'begin
            (append (list 'define* decl) b)
            (list 'set! (list 'documentation (quote ',name)) d)))))
(set! (documentation 'defun*) "define a function in emacs style")

(defmacro* defvar (name #:optional init docstring)
  `(let ((d ',docstring))
     (if (not (test-string ',docstring))
         (set! d "undocumented"))
     (primitive-eval
      (list 'begin
            (list 'define ',name ',init)
            (list 'set! (list 'documentation (quote ',name)) d)))))
(set! (documentation 'defvar) "define a variable in emacs style")
