#!/bin/bash
#!/bin/bash

echo "=== Nettoyage des headers ==="

# 1. Sauvegarde
echo ">>> Création d'une sauvegarde git (branch de sécurité)"
git add . > /dev/null 2>&1
git commit -m "Backup avant cleanup headers" > /dev/null 2>&1

# 2. Remplacer t_minishell par t_shell partout
echo ">>> Remplacement de 't_minishell' par 't_shell'..."
find SRC include -type f \( -name "*.c" -o -name "*.h" \) -exec sed -i 's/t_minishell/t_shell/g' {} +

# 3. Remplacer l'inclusion de parsking.h par minishell.h
echo ">>> Remplacement de #include \"parsking.h\" par #include \"minishell.h\"..."
find SRC include -type f \( -name "*.c" -o -name "*.h" \) -exec sed -i 's/#include *"parsking.h"/#include "minishell.h"/g' {} +

# 4. Supprimer la struct t_minishell (au cas où elle existe encore)
echo ">>> Suppression de la struct t_minishell..."
sed -i '/typedef struct s_minishell/,/}.*t_minishell;/d' include/minishell.h

# 5. Vérification
echo ">>> Vérification des occurrences restantes..."
grep -rnw "SRC" -e "t_minishell" || echo "OK: Aucun 't_minishell' dans SRC."
grep -rnw "include" -e "t_minishell" || echo "OK: Aucun 't_minishell' dans include."

echo "=== Nettoyage terminé ==="
echo ">>> Tu peux maintenant lancer 'make re'."
