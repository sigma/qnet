(define-module (general font-lock))

(export font-lock-add-keywords
        font-lock)

(use-modules (general utils))
(use-modules (general doc))
(use-modules (internal)) ;; some are natives functions

(defun make-face (f)
  (cond ((pair? f)
         (new-face (car f) (cdr f)))
        ((symbol? f)
         (new-face (car (symbol-value f)) (cdr (symbol-value f))))))

(defvar font-lock-keywords '())

(defun font-lock-add-keywords (list)
  "Add some keywords"
  (set! font-lock-keywords
        (append list font-lock-keywords)))

(defun font-lock ()
  (let* ((n (- (qnet-sessions-number mtp) 1))
         (lock (chat-page-font-lock (chatsession-chatpage (qnet-session mtp n)))))
    (map (lambda (l)
           (let ((pat (new-pattern (car l))))
             (map (lambda (e)
                    (pattern-add pat (car e) (make-face (cdr e))))
                  (car (cdr l)))
             (font-lock-add-pattern lock pat)))
         font-lock-keywords)))