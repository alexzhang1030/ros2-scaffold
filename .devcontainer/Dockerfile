ARG DOCKER_REPO
ARG ROS_DISTRO
ARG IMAGE_SUFFIX
FROM $DOCKER_REPO:$ROS_DISTRO$IMAGE_SUFFIX
ARG USERNAME
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Setup LazyGit
RUN LAZYGIT_VERSION=0.52.0 && \
  curl -Lo lazygit.tar.gz "https://github.com/jesseduffield/lazygit/releases/download/v${LAZYGIT_VERSION}/lazygit_${LAZYGIT_VERSION}_Linux_x86_64.tar.gz" && \
  tar xf lazygit.tar.gz lazygit && \
  sudo install lazygit -D -t /usr/local/bin/ && \
  rm -rf lazygit.tar.gz lazygit

# Long-term no-update dependencies
RUN apt-get update && apt-get upgrade -y && apt-get install -y sudo git curl wget zsh vim neovim zsh-autosuggestions zsh-syntax-highlighting

# Add user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Set the default user
USER $USERNAME

ENV ZSH_CUSTOM /home/$USERNAME/.oh-my-zsh/custom
ENV ZDOTDIR /home/$USERNAME

# oh-my-zsh
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
RUN git clone https://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions --depth=1
RUN git clone https://github.com/zsh-users/zsh-syntax-highlighting.git $ZSH_CUSTOM/plugins/zsh-syntax-highlighting --depth=1
RUN git clone https://github.com/spaceship-prompt/spaceship-prompt.git "$ZSH_CUSTOM/themes/spaceship-prompt" --depth=1
RUN ln -s "$ZSH_CUSTOM/themes/spaceship-prompt/spaceship.zsh-theme" "$ZSH_CUSTOM/themes/spaceship.zsh-theme"
RUN sed -i 's/^plugins=(.*/plugins=(git zsh-autosuggestions zsh-syntax-highlighting)/g' /home/$USERNAME/.zshrc
RUN sed -i 's/^ZSH_THEME=.*/ZSH_THEME="spaceship"/g' /home/$USERNAME/.zshrc

# Make default shell zsh
ENV SHELL /bin/zsh

# Source ROS environment automatically
RUN echo "source /opt/ros/$ROS_DISTRO/setup.zsh" >> /home/$USERNAME/.zshrc && \
    echo "source /home/ws/install/setup.zsh" >> /home/$USERNAME/.zshrc && \
    echo "alias lg='lazygit'" >> /home/$USERNAME/.zshrc

CMD ["/bin/zsh"]
