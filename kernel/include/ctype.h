#ifndef CTYPE_H
#define CTYPE_H

	
// Digits
// This is a set of whole numbers { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.

// Hexadecimal digits
// This is the set of { 0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f }.

// Lowercase letters
// This is a set of lowercase letters { a b c d e f g h i j k l m n o p q r s t u v w x y z }.

// Uppercase letters
// This is a set of uppercase letters {A B C D E F G H I J K L M N O P Q R S T U V W X Y Z }.

// Letters
// This is a set of lowercase and uppercase letters.

// Alphanumeric characters This is a set of Digits, Lowercase letters and Uppercase letters.

// Punctuation characters
// This is a set of ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~
	
// Graphical characters
// This is a set of Alphanumeric characters and Punctuation characters.

// Space characters 
// This is a set of tab, newline, vertical tab, form feed, carriage return, and space.

int isalnum  (int c); //This function checks whether the passed character is alphanumeric.
int isalpha  (int c); //This function checks whether the passed character is alphabetic.
int iscntrl  (int c); //This function checks whether the passed character is control character.
int isdigit  (int c); //This function checks whether the passed character is decimal digit.
int isgraph  (int c); //This function checks whether the passed character has graphical representation using locale.
int islower  (int c); //This function checks whether the passed character is lowercase letter.
int isprint  (int c); //This function checks whether the passed character is printable.
int ispunct  (int c); //This function checks whether the passed character is a punctuation character.
int isspace  (int c); //This function checks whether the passed character is white-space.
int isupper  (int c); //This function checks whether the passed character is an uppercase letter.
int isxdigit (int c); //This function checks whether the passed character is a hexadecimal digit.

#endif