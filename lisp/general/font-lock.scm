(define-module (general font-lock))

(export blue-face
        yellow-face
        red-face
        font-lock-add-keywords)

(use-modules (general utils))
(use-modules (general doc))
(use-modules (internal)) ;; some are natives functions

(defvar blue-face '("arial" . "blue"))
(defvar yellow-face '("verdana" . "yellow"))
(defvar red-face '("times" . "red"))

(defun make-face (f)
  (cond ((pair? f)
         (new-face (car f) (cdr f)))
        ((symbol? f)
         (new-face (car (symbol-value f)) (cdr (symbol-value f))))))

(defun font-lock-add-keywords (n pattern list)
  "Add some keywords"
  (let* ((lock (chat-page-font-lock (chatsession-chatpage (qnet-session mtp n))))
         (pat (new-pattern pattern)))
    (map (lambda (e)
           (pattern-add pat (car e) (make-face (cdr e))))
         list)
    (font-lock-add-pattern lock pat)
    ))
