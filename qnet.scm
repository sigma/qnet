(set! %load-path (append %load-path (list (string-append (getenv "HOME") "/.qnet/lisp"))))

(use-modules (general doc))
(use-modules (general font-lock))
(use-modules (general utils))

(defvar mtp (mainwin-qmtp (main-window)))

(defun launch (s)
  (qnet-launch-session mtp s))

(defun session-name (n)
  (if (< n (qnet-sessions-number mtp))
      (chatsession-session-name (qnet-session mtp n))
      nil))

(defun send (session mesg)
  (if (< session (qnet-sessions-number mtp))
      (chatsession-send (qnet-session mtp session) mesg)))

(defun make-face (f)
  (cond ((pair? f)
         (new-face (car f) (cdr f)))
        ((symbol? f)
         (new-face (car (symbol-value f)) (cdr (symbol-value f))))))

(defun font-lock-add-keywords (n pattern list)
  (let* ((lock (chat-page-font-lock (chatsession-chatpage (qnet-session mtp n))))
         (pat (new-pattern pattern)))
    (map (lambda (e)
           (pattern-add pat (car e) (make-face (cdr e))))
         list)
    (font-lock-add-pattern lock pat)
    ))

(defun font-lock ()
  (font-lock-add-keywords (- (qnet-sessions-number mtp) 1)
                          "<(Mtp)> (.*)" '((1 . yellow-face)
                                           (2 . red-face))))

; (add-hook! chatsession-created-hook font-lock)

(defun plip ()
  (chat-page-toggle-user-box (chatsession-chatpage (qnet-session mtp 0))))
