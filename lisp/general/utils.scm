(define-module (general utils))

(export symbol-value)

(use-modules (general doc))

(defun symbol-value (s)
  (if (symbol? s)
      (primitive-eval s)
      (error "Not a symbol !")))
