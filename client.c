/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:15:10 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/16 13:31:19 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// How does minitalk will work ?
// The goal : send a message (string of ASCII characters) from client to server.
// - The two programs can ONLY communicate by using SIGUSR1 and SIGUSR2 signals.
// - An ASCII character is 8 bits long. For example, the letter A is 01000001.
// - When the client send "ABC" to the senver, it will send 8*3 = 24 signals.
// - The first 8 signals represent the 'A', the 8 next the 'B' and so on.
// - To send 01000001, the client will send :
// - SIGUSR2 (0)
// - SIGUSR1 (1)
// - SIGUSR2 (0)
// - SIGUSR2 (0)
// - SIGUSR2 (0)
// - SIGUSR2 (0)
// - SIGUSR1 (1)
// - SIGUSR1 (1)
// - The server will do nothing until it recieves 8 signals.
// - At every signal, the server will store the binary value of the signal.
// - Server will send SIGUSR1 to client if everying is ok.
// - If something failed, the server will send SIGUSR2 to client.
// - When the server recieves 8 signals, it will convert the binary value
//   we stored into a decimal value. In this case, 01000001 = 65.
//   65 is the ASCII code of the letter A.
// - Then print this ASCII code on the screen with write().
//
// - The client repeats this process for 'B' and 'C' and for '\0'.
// - If the server recieves 8 SIGUSR2 signals, it means that the client
//   sent the '\0' character, meaning that the message is over.
// - The client program will stop sending signals and the server will
//   idle until it recieves a new message.
//
// To make it clear :
// CLIENT --> SERVER    SERVER --> CLIENT
// SIGUSR1 = 1          SIGUSR1 = I got your message
// SIGUSR2 = 0          SIGUSR2 = I didn't get your message

