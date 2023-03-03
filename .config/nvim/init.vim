" this file is copyright free (public domain)



" --{ autoinstall command }--
    if ! filereadable(system('echo -n "${XDG_CONFIG_HOME:-$HOME/.config}/nvim/autoload/plug.vim"'))
        echo "Downloading vim-plug to manage plugins..."
        silent !mkdir -p ${XDG_CONFIG_HOME:-$HOME/.config}/nvim/autoload/
        silent !curl "https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim" > ${XDG_CONFIG_HOME:-$HOME/.config}/nvim/autoload/plug.vim
        autocmd VimEnter * PlugInstall
    endif



" ---{ sane defaults }---
filetype plugin on " enter the 21st century
let mapleader=" "
nnoremap c "_c
syntax on

set backspace=indent,eol,start
set cindent
set clipboard^=unnamed,unnamedplus
set cursorline
set cursorcolumn
" set colorcolumn=80
set encoding=utf-8
" set expandtab
set go=a
set ignorecase
set incsearch
set lcs=tab:>-,lead:•,trail:~
set mouse=a
set nobackup
set noerrorbells
set nohlsearch
set noshowcmd
set nu rnu
set path+=**
set ruler
set scrolloff=4
set shiftwidth=4
set showtabline=2
set sidescrolloff=4
set signcolumn=yes
set smartcase
set smartindent
set splitbelow splitright
set tabstop=4
set title
set viewoptions=cursor,folds,slash,unix
set wildignore=*.docx,*.exe,*.flv,*.gif,*.img,*.jpg,*.odt,*.pdf,*.png,*.pyc,*.xlsx
set wildmenu
set wildmode=list,full

" subtle tweaks for reading diffs
    if &diff
        highlight! link DiffText MatchPattern
    endif
" clear all trailing whitespace and newlines on save
    autocmd BufWritePre * let currPos = getpos(".")
    autocmd BufWritePre * %s/\s\+$//e
    autocmd BufWritePre * %s/\n\+\%$//e
    autocmd BufWritePre *.[ch] %s/\%$/\r/e
    autocmd BufWritePre * cal cursor(currPos[1], currPos[2])
" clear out TeX build files when closing a .tex file
    autocmd VimLeave *.tex !texclear %
" disable automatic commenting on new lines
    autocmd FileType * setlocal formatoptions-=c formatoptions -=r formatoptions-=o
" netrw tweaks (for those who don't want NERDTree)
    let g:netrw_list_hide=netrw_gitignore#Hide()
    let g:netrw_list_hide.=',\(^\|\s\s\)zs\.\S+'
    let g:netrw_banner=0       " disable horrible banner
    let g:netrw_browse_split=3 " open in prior window
    let g:netrw_altv=1         " open split to the right
    let g:netrw_liststyle=3    " tree view
" quick load/edit (n)vim configuration
    map <Leader>ve :edit $HOME/.config/nvim/init.vim<CR>
    map <Leader>vr :source $HOME/.config/nvim/init.vim<CR>
    " map <Leader>ve :edit $HOME/.vimrc<CR>
    " map <Leader>vr :source $HOME/.vimrc<CR>
" read files as desired
    let g:vimwiki_ext2syntax = {'.md': 'markdown', '.markdown': 'markdown', '.mdown': 'markdown'}
    let g:vimwiki_list = [{'path': '$HOME/.local/share/nvim/vimwiki', 'syntax': 'markdown', 'ext': '.md'}]
    autocmd BufRead,BufNewFile /tmp/calcurse*,~/.calcurse/notes/* set filetype=markdown
    autocmd BufRead,BufNewFile *.ms,*.me,*.mom,*.man set filetype=groff
    autocmd BufRead,BufNewFile *.Rmd,*.rmd set filetype=rmd
    autocmd BufRead,BufNewFile *.tex set filetype=tex
" save files with elevated permissions without closing
    cnoremap w!! execute 'silent! write !doas tee % >/dev/null' <bar> edit!
    " cnoremap w!! execute 'silent! write !sudo tee % >/dev/null' <bar> edit!
" run xrdb whenever xresources or xdefaults are updated
    autocmd BufRead,BufNewFile Xresources,Xdefaults,xresources,xdefaults set filetype=xdefaults
    autocmd BufWritePost Xresources,Xdefaults,xresources,xdefaults !xrdb %



" ---{ plugins }---
call plug#begin(system('echo -n "${XDG_CONFIG_HOME:-$HOME/.config}/nvim/vimplug"'))
  " for function
    Plug 'airblade/vim-gitgutter'
    Plug 'folke/which-key.nvim'
    Plug 'gentoo/gentoo-syntax'
    Plug 'jiangmiao/auto-pairs'
    Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
    Plug 'junegunn/fzf.vim'
    Plug 'junegunn/goyo.vim'
    " Plug 'junegunn/limelight.vim'
    Plug 'kshenoy/vim-signature'
    " Plug 'preservim/nerdtree'
    Plug 'ptzz/lf.vim'
    Plug 'tpope/vim-commentary'
    Plug 'tpope/vim-fugitive'
    Plug 'tpope/vim-sensible'
    Plug 'tpope/vim-speeddating'
    Plug 'tpope/vim-surround'
    Plug 'tpope/vim-unimpaired'
    Plug 'tpope/vim-vinegar'
    Plug 'wesQ3/vim-windowswap'
    Plug 'vim-pandoc/vim-pandoc-syntax'
    Plug 'vim-scripts/restore_view.vim'
    Plug 'vimwiki/vimwiki'
    Plug 'voldikss/vim-floaterm'
    Plug 'xolox/vim-misc'
    Plug 'xolox/vim-session'
  " for looks
    Plug 'itchyny/lightline.vim'
    Plug 'rose-pine/neovim', { 'as': 'rose-pine' }
call plug#end()



" ---{ custom commands and functions }---
" ctags integration
    command! MakeTags !ctags -R .


" ---{ which-key }---
lua << EOF
  require("which-key").setup {
    icons = {
      separator = "➜ ", -- symbol used between a key and it's label
    }
}
EOF
