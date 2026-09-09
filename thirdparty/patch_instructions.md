Because standard git diff only compares tracked files against the current index,
it inherently ignores all untracked
CMake cache files, generated build artifacts, and clutter.

### Navigate to the repository:

Change your working directory to the root of the source fetched by CMake.

```
cd /build/dep_/[something]_src
```

### Verify Upstream Repository

```
git remote -v
```

Expected result:

    origin  https://github.com/[GITHUB_REPO].git (fetch)
    origin  https://github.com/[GITHUB_REPO].git (push)

### Verify Modified Files:

Check the status of tracked files while explicitly hiding untracked files using
the -uno (hide untracked normal output)
flag.

```
git status -uno
```

Expected result:

    HEAD detached at v35.1
    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
            modified:   cmake/abseil-cpp.cmake
            modified:   src/google/protobuf/map.h
    
    no changes added to commit (use "git add" and/or "git commit -a")

To verify this step, ensure the output under "Changes not staged for commit"
exclusively lists the specific C++ headers and source files you manually edited.

### Generate the Minimal Patch

Output the exact differences of your unstaged modifications and redirect them
into a .patch file.

```
git diff | Out-File -Encoding utf8 [patch_name].patch
```

There will be no output in the CLI, but your file will be saved in the directory
it is currently looking at.

To verify the extraction was successful, read the first few lines of the file
using head
protobuf_cxx_module_inline.patch or open it in a text editor. It should start
with standard Git diff headers (e.g., diff
--git a/...) and only contain your +inline additions.

### Change Patch File to UTF-8 (Windows PowerShell)

If you created this patch file using Windows PowerShell, it defaults to saving
files in UTF-16 LE encoding. Git does not understand UTF-16; it reads it as a
corrupted binary file, sees no readable patch headers, and throws this exact
error.

How to fix it:

    Quick fix: Open the .patch file in Notepad, click File > Save As, and change the "Encoding" dropdown at the bottom from UTF-16 LE to UTF-8. Save and overwrite the file, then re-run CMake.

    Future fix: If generating patches in PowerShell, force UTF-8 encoding like this:
    PowerShell

    git diff | Out-File -Encoding utf8 protobuf_cxx_module_fix_v35-1.patch

    (Alternatively, generate your patches using Git Bash, which uses UTF-8 natively).