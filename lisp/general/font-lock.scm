(define-module (general font-lock))

(export font-lock-install
        font-lock-add-keywords
        font-lock-add-blocks
        font-lock-blocks
        font-lock
        defface
        make-face
        font-lock-default-family
        font-lock-default-color
        font-lock-default-size
        font-lock-default-weight
        font-lock-default-italic
        default-face)

(use-modules (general utils)
             (general doc)
             (internal)
             (ice-9 optargs)) ;; some are natives functions

(defun make-face (f)
  (cond ((pair? f)
         ;(primitive-eval '(append (new-face) f))
         (new-face (list-ref f 0) (list-ref f 1) (list-ref f 2) (list-ref f 3) (list-ref f 4))
         )
        ((symbol? f)
         (make-face (symbol-value f)))))

(defvar font-lock-default-family "verdana")
(defvar font-lock-default-color "black")
(defvar font-lock-default-size 12)
(defvar font-lock-default-weight 'normal)
(defvar font-lock-default-italic #f)

(defmacro* defface (name #:key
                         (family font-lock-default-family)
                         (color font-lock-default-color)
                         (size font-lock-default-size)
                         (weight font-lock-default-weight)
                         (italic font-lock-default-italic))
  `(defvar ,name
     (list ,family
           ,color
           ,size
           ,(primitive-eval (list (string->symbol (string-append "face-" (symbol->string weight)))))
           ,italic)))

(defvar font-lock-keywords '())
(defvar font-lock-blocks '())

(defun font-lock-add-keywords (fl list)
  "Add some keywords"
  (set! font-lock-keywords
        (append font-lock-keywords list)))

(defun font-lock-add-blocks (fl list)
  "Add some blocks"
  (set! font-lock-blocks
        (append font-lock-blocks list)))

;; todo: make this function smarter (accept various formats) by pre-formatting l
(defun font-lock-install (lock)
  "fontify last opened session"
  (font-lock-clear lock)
  (map (lambda (l)
         (let ((pat (new-pattern (car l))))
           (map (lambda (e)
                  (pattern-add pat (car e) (make-face (cdr e))))
                (car (cdr l)))
           (font-lock-add-pattern lock pat)))
       font-lock-keywords)
  (map (lambda (l)
         (let ((pat1 (new-pattern (car (list-ref l 0))))
               (pat2 (new-pattern (car (list-ref l 1))))
               (pat3 (new-pattern (car (list-ref l 2)))))
           (map (lambda (e)
                  (pattern-add pat1 (car e) (make-face (cdr e))))
                (car (cdr (list-ref l 0))))
           (map (lambda (e)
                  (pattern-add pat2 (car e) (make-face (cdr e))))
                (car (cdr (list-ref l 1))))
           (map (lambda (e)
                  (pattern-add pat3 (car e) (make-face (cdr e))))
                (car (cdr (list-ref l 2))))
           (font-lock-add-multi-pattern lock (new-block-pattern pat1 pat3 pat2))))
       font-lock-blocks))

(defface default-face #:family "verdana" #:color "black")
(face-set-default-face (make-face default-face))
