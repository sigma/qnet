(define-module (general utils))

(export symbol-value
        nth)

(use-modules (general doc)
             (internal))

(defun symbol-value (s)
  (if (symbol? s)
      (primitive-eval s)
      (error "Not a symbol !")))

(defmacro nth (n l)
  `(list-ref ,l ,n))