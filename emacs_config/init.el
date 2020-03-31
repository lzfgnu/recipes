(package-initialize)
(add-to-list 'load-path "~/.emacs.d/init/basic")
(add-to-list 'load-path "~/.emacs.d/init/pkgs/")

(require 'init-pkgs)
(require 'init-basic)


(defun open-init-file ()
  (interactive)
  (find-file "~/.emacs.d/init.el"))
