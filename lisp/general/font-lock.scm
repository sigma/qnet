(define-module (general font-lock))

(export font-lock-add-keywords
        font-lock-add-blocks
        font-lock-blocks
        font-lock
        defface
        font-lock-default-family
        font-lock-default-color
        font-lock-default-size
        font-lock-default-weight
        font-lock-default-italic)

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
(defvar font-lock-default-weight 50)
(defvar font-lock-default-italic 0)

(defmacro* defface (name #:key
                         (family font-lock-default-family)
                         (color font-lock-default-color)
                         (size font-lock-default-size)
                         (weight font-lock-default-weight)
                         (italic font-lock-default-italic))
  `(defvar ,name
     (list ,family ,color ,size ,weight ,italic)))

(defvar font-lock-keywords '())
(defvar font-lock-blocks '())

(defun font-lock-add-keywords (list)
  "Add some keywords"
  (set! font-lock-keywords
        (append list font-lock-keywords)))

(defun font-lock-add-blocks (list)
  "Add some blocks"
  (set! font-lock-blocks
        (append list font-lock-blocks)))


(defun font-lock ()
  (let* ((n (- (qnet-sessions-number mtp) 1))
         (lock (chat-page-font-lock (chatsession-chatpage (qnet-session mtp n)))))
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
         font-lock-blocks)))