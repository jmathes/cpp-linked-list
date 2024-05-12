# POC Linked List class

## Installation Instructions

### Installing Dependencies

1. Update and upgrade your package lists:

   ```bash
   sudo apt-get update
   sudo apt-get upgrade

    sudo apt-get update
    sudo apt-get upgrade
    sudo apt-get -f install

    sudo apt install apt-transport-https curl gnupg
    curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor >bazel-archive-keyring.gpg
    sudo mv bazel-archive-keyring.gpg /usr/share/keyrings
    echo "deb [signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
    sudo apt update && sudo apt install bazel
   ```

2. Building the Library:

   ```bash
   bazel build linked_list_lib
   ```

3. Running tests:
   ```bash
   bazel test linked_list_test
   ```
