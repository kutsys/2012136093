# ~/.bashrc: executed by bash(1) for non-login shells.
#// 비 로그인 쉘에 대한 bash는 (1)에 의해 실행된다.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
#// 참조는 /usr/share/doc/bash/examples/startup-files에서 한다.
# for examples
#// 예시들

# If not running interactively, don't do anything
#//만약 상호작용으로 실행되지 않는다면, 아무것도 일어나지 않는다.
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
#// 중복되는 line이나 history 앞에 빈 공간을 넣지 말아라.
# See bash(1) for more options
#// 더 많은 bash(1)의 옵션이 있다.
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
#// history파일을 추가하며, 그것을 덮어 쓰지 않는다.
shopt -s histappend 

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
#// history 길이를 설정하기 위해서, bash(1)에 HISTSIZE, HISTFILESIZE를 보아라
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
#// 필요한 경우, 각각의 명령 후에 창 크기를 확인하고,
# update the values of LINES and COLUMNS.
#// 행과 열의 값을 업데이트 한다.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
#// 만약 경로 이름에 **를 넣는다면
# match all files and zero or more directories and subdirectories.
#// 0부터 모든 디렉토리와 서브디렉토리를 검사하게 될 것 이다.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
#// less를 이용해 비 텍스트 파일을 더 친화적으로 만든다.
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
#// 당신이 사용하는 chroot를 식별하는 변수를 설정한다.(사용하는 prompt 아래)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
#// 멋진 프롬프트를 설정
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
#// 만약 터미널이 사용가능하다면, 컬러 프롬프트에 대한 주석을 단다.
# off by default to not distract the user: the focus in a terminal window
#// 사용자가 혼란을 겪지 않도록 디폴트를 해제한다. 터미널 윈도우에 집중한다.
# should be on the output of commands, not on the prompt
#// 명령어로써 결과가 나온다면, 프롬프트가 아니다.
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
    # We have color support; assume it's compliant with Ecma-48
    # (ISO/IEC-6429). (Lack of such support is extremely rare, and such
    # a case would tend to support setf rather than setaf.)
    color_prompt=yes
    else
    color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
#// 만약 이것이 xterm일 경우 제목을 user@host:dir로 설정.
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
#// ls가 색상지원을 가능하게 하고 편리한 명령어를 추가할 수 있음.
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# colored GCC warnings and errors
#// 컬러로 된 GCC 에러 메시지 색깔
#export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# some more ls aliases
#// 좀더 많은 ls 명렁어들
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# Add an "alert" alias for long running commands.  Use like so:
#// 동작시간이 길다면 alias에 "alter"를 추가한다. 다음과 같이 사용하라.
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
#// 명렁어 정의
# You may want to put all your additions into a separate file like
#// 당신은 추가적으로 생성된 파일에 집어넣고 싶어할 수도 있다. 
# ~/.bash_aliases, instead of adding them here directly.
#// ~/.bash_aliases 여기에 직접추가하는것 대신에
# See /usr/share/doc/bash-doc/examples in the bash-doc package.
#//  bash-doc에있는 /usr/share/doc/bash-doc/examples를 보아라

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
#// 프로그래밍이 가능한 이미 있는 특징들의 사용 (너는 사용 할 필요를 느끼지 않을 것 이다.
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
#// ,만약 이것들이 모두 in /etc/bash.bashrc와 /etc/profile에서 사용가능하다면
# sources /etc/bash.bashrc).
#// /etc/bash.bashrc 에서)
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

