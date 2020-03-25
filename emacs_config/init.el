(package-initialize)
(add-to-list 'load-path "~/.emacs.d/init/")

(require 'init-pkgs)
(require 'init-defaults)
(require 'init-ui)
(require 'init-file-mode)
(require 'init-keybindings)


(defun open-init-file ()
  (interactive)
  (find-file "~/.emacs.d/init.el"))
