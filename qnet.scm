(set! %load-path (append %load-path (list (string-append (getenv "HOME") "/.qnet/lisp"))))

(use-modules (general doc)
             (general font-lock)
             (general utils)
             (internal)
             (xosdguile)
             (ice-9 regex))

(set! font-lock-default-size 10)

(defface blue-face #:family "arial" #:color "blue")
(defface yellow-face #:family "verdana" #:color "yellow")
(defface red-face #:family "times" #:color "red")

(defface block-face #:family "monospace" #:color "black")
(defface server-face #:family "verdana" #:color "blue" #:italic 1)
(defface me-face #:family "verdana" #:color "darkblue" #:weight 75)
(defface other-face #:family "verdana" #:color "pink")
(defface emote-face #:family "verdana" #:color "green")
(defface tome-face #:family "verdana" #:color "red")
(defface default-face #:family "verdana" #:color "black")
(defface url-face #:family "verdana" #:color "orange")

(defface emacs-face #:family "verdana" #:color "green" #:weight 75)

(defface blue-face #:family "verdana" #:color "blue" #:weight 75)
(defface green-face #:family "verdana" #:color "green" #:weight 75)
(defface yellow-face #:family "verdana" #:color "yellow" #:weight 75)
(defface orange-face #:family "verdana" #:color "orange" #:weight 75)
(defface red-face #:family "verdana" #:color "red" #:weight 75)

; (add-hook! chatsession-output-hook output-filter)
(add-hook! chatsession-created-hook font-lock)

(font-lock-add-keywords '(
                          ("^<Mtp>.*"
                           ((0 . server-face)))
                          ("^<Mtp> \\*.*"
                           ((0 . emote-face)))
                          ("^<Mtp> You.*"
                           ((0 . other-face)))
                          ("([Ee])([Mm])([Aa])([Cc])([Ss])"
                           ((1 . blue-face)
                            (2 . green-face)
                            (3 . yellow-face)
                            (4 . orange-face)
                            (5 . red-face)))
                          ))

(font-lock-add-blocks '(
                        ;; Wall
                        (("^<Mtp> Wall :" ((0 . block-face)))
                         ("^.*" ((0 . block-face)))
                         ("^<Mtp> End of Wall :" ((0 . block-face))))
                        ;; Msg
                        (("^<Mtp> Your message" ((0 . other-face)))
                         ("^.*" ((0 . default-face)))
                         ("^<Mtp> You have" ((0 . me-face))))
                        ;; Who
                        (("^ Login .*" ((0 . block-face)))
                         ("^.*" ((0 . block-face)))
                         ("^(<Mtp> .*)" ((1 . server-face))))
                        ;; Info
                        (("^(<Mtp> History.*|<Mtp> System.*|<Mtp> Help.*|Welcome to.*)" ((0 . block-face)))
                         ("^.*" ((0 . block-face)))
                         ("^<.*" ((0 . server-face))))
                        ))

(defun plip ()
  (chat-page-toggle-user-box (chatsession-chatpage (qnet-session mtp 0))))

(defvar osd-size 5)
(defvar osd-timeout 5)
(defvar osd (make-xosd osd-size))
(defvar osd-position '(80 . 0))

(xosd-timeout! osd osd-timeout)
(xosd-pos! osd 'bottom)
(xosd-align! osd 'center)
(xosd-horizontal-offset! osd (car osd-position))
(xosd-vertical-offset! osd (cdr osd-position))

(add-hook! chatsession-created-hook (lambda ()
                                      (xosd-hide osd)
                                      (xosd-display-string osd 0 "New ChatSession !")))

; (add-hook! chatsession-output-hook (lambda (s)
;                                      (xosd-scroll osd 1)
;                                      (xosd-display-string osd (- osd-size 1) s)))
