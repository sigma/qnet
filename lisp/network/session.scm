(define-module (network session))

(export define-session
        launch-session
        default-host
        default-port
        default-login
        default-passwd
        default-proto
        default-output
        )

(use-modules (internal)
             (general doc)
             (general utils)
             (ice-9 optargs))

(defvar default-host "localhost")
(defvar default-port 4000)
(defvar default-login #f)
(defvar default-passwd #f)
(defvar default-proto 'mtp)
(defvar default-output '())

(defmacro* define-session (name #:key (host default-host)
                                (port default-port)
                                (login default-login)
                                (passwd default-passwd)
                                (proto default-proto)
                                (output default-output))
  `(defvar ,name (list ,host ,port ,login ,passwd ',proto ',output)))

(defun launch-session (session)
  (let* ((host (nth 0 session))
         (port (nth 1 session))
         (login (nth 2 session))
         (passwd (nth 3 session))
         (proto (nth 4 session))
         (output (nth 5 session))
         (sock (new-mtpsocket))
         (mtp (new-mtpprotocol))
         (disp (new-dispatcher mtp))
         (ft (main-window-get-floating-tab (mw)))
         (ed (new-mtparea))
         (ed2 (new-mtparea))
         (proto-func (symbol-prefix-proc proto))
         )

    (mtpsocket-set-host sock host)
    (mtpsocket-set-port sock port)
    (if login
      (mtpsocket-set-login sock login))
    (if passwd
      (mtpsocket-set-passwd sock passwd))

    (primitive-eval (list (apply proto-func 'protocol-install-io '()) mtp sock))

    (map (lambda (out)
           (let ((ed (new-mtparea)))
             (floating-tab-add-tab ft ed out)
             (dispatcher-add-interaction-area disp ed)))
         output)

    (mtpsocket-connet-to-host sock))

)