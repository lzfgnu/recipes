(package-initialize)
(add-to-list 'load-path "~/.emacs.d/lisp/")

(require 'init-pkgs)
(require 'init-defaults)
(require 'init-keybindings)
(require 'init-ui)


(defun open-init-file ()
  (interactive)
  (find-file "~/.emacs.d/init.el"))

