(set! %load-path (append %load-path (list (string-append (getenv "HOME") "/.qnet/lisp"))))

(use-modules (general doc))
(use-modules (general font-lock))
(use-modules (general utils))
(use-modules (internal))

(add-hook! chatsession-created-hook font-lock)

(defvar blue-face '("arial" . "blue"))
(defvar yellow-face '("verdana" . "yellow"))
(defvar red-face '("times" . "red"))

(font-lock-add-keywords '(("<(Mtp)> (.*)" ((1 . yellow-face)
                                           (2 . red-face)))))

(defun plip ()
  (chat-page-toggle-user-box (chatsession-chatpage (qnet-session mtp 0))))
