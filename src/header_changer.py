import sys
import os

def copy_file(file_name):
    with open(file_name, 'r') as file_to_edit:
        copy = file_to_edit.read()
    copy = str(copy)
    return copy

def edit_user_login(login, copy):
    copy = replace_user_email(login, copy)
    copy = replace_user_login(login, copy)
    return copy

def replace_user_email(login, copy):
    logins_to_delete = [
            "/*   By: piranucci <piranucci@student.42.fr>        +#+  +:+       +#+        */",
            "/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */",
            "/*   By: piranucc <piranucci@student.42.fr>         +#+  +:+       +#+        */",
            "/*   By: piranucc <marvin@42.fr>                    +#+  +:+       +#+        */",
            "/*   By: lprunier <lprunier@student.42.fr>          +#+  +:+       +#+        */",
            "/*   By: lprunier <marvin@student.42.fr>            +#+  +:+       +#+        */",
            ]
    correct_line = "/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */"
    for searched_login in logins_to_delete:
        if copy.find(searched_login) != -1:
            copy = copy.replace(searched_login, correct_line)
    return copy

def replace_user_login(login, copy):
    logins_to_delete = ["lprunier", "piranucc"]
    for searched_login in logins_to_delete:
        login = login.ljust(len(login) + (len(searched_login) - len(login)), ' ')
        if copy.find(searched_login) != -1:
            copy = copy.replace(searched_login, login)
    return copy

def edit_file(copy, file_name):
    with open(file_name, 'w') as file_to_edit:
        file_to_edit.write(copy)

def change_file_header(login, file_name):
    copy = copy_file(file_name)
    copy = edit_user_login(login, copy)
    edit_file(copy, file_name)

login = sys.argv[1]
repertory_name = sys.argv[2]
current_path = os.getcwd()
repertory = current_path + '/' + repertory_name
repertory_content = os.listdir(repertory)
for content in repertory_content:
    file_name = repertory + '/' + content
    if file_name != repertory + '/' + "auteur":
        print(file_name)
        change_file_header(login, file_name)

