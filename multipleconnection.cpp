// int max_sd;
// fd_set readfds;
// const char *message = "ECHO Daemon v1.0 \r\n"; 
// 	while(1)  
//     {  
//         //clear the socket set 
//         FD_ZERO(&readfds);  
//     //  
//         //add master socket to set 
//         FD_SET(server.server_fd, &readfds);  
//         max_sd = server.server_fd;  
             
//         //add child sockets to set 
//         for (int i = 0 ; i < MAX_CLIENTS; i++)  
//         {  
//             //socket descriptor 
//             int sd = server.client_socket[i];
                 
//             //if valid socket descriptor then add to read list 
//             if(sd > 0)  
//                 FD_SET( sd , &readfds);

//             //highest file descriptor number, need it for the select function 
//             if(sd > max_sd)  
//                 max_sd = sd;  
//         }  

//         //wait for an activity on one of the sockets , timeout is NULL , 
//         //select fonksiyonu, bir veya daha fazla dosya tanımlayıcısının okunabilir, 
// 		//yazılabilir veya özel durum durumlarında olduğunu kontrol ederek işlem yapmayı sağlar.
// 		//EINTR, bir işlem sırasında sinyal alındığında oluşan bir hata kodudur ve işlemi yeniden başlatmak gerektirir.
//         int activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
//         if ((activity < 0) && (errno != EINTR))  
//         {  
//             printf("select error");  
//         }  
             
//         //If something happened on the master socket , 
//         //then its an incoming connection 
//         if (FD_ISSET(server.server_fd, &readfds))  
//         {  
//             if ((server.new_socket = accept(server.server_fd, 
//                     (struct sockaddr *)&server.address, (socklen_t*)&server.addr_len)) < 0)  
//             {  
//                 perror("accept");  
//                 exit(EXIT_FAILURE);  
//             }  
             
//             //send new connection greeting message 
//             if (send(server.new_socket, message, strlen(message), 0) != static_cast<long>(strlen(message)))
//             {  
//                 perror("send");  
//             }  
//             //add new socket to array of sockets 
//             for (int i = 0; i < MAX_CLIENTS; i++)  
//             {  
//                 //if position is empty 
//                 if(server.client_socket[i] == 0 )  
//                 {  
//                     server.client_socket[i] = server.new_socket;  
//                     printf("Adding to list of sockets as %d\n" , i);  
//                     break;  
//                 }  
//             }  
//         }  
             
//         //else its some IO operation on some other socket
//         for (int i = 0; i < MAX_CLIENTS; i++)  
//         {  
//             int sd = server.client_socket[i];  
                 
//             if (FD_ISSET( sd , &readfds))  
//             {  
//                 //Check if it was for closing , and also read the 
//                 //incoming message 
// 				int valread;
//                 if ((valread = read( sd , server.buffer, 1024)) == 0)  
//                 {  
//                     //Somebody disconnected , get his details and print 
//                     getpeername(sd , (struct sockaddr*)&server.address , \
//                         (socklen_t*)&server.addr_len);  
//                     printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(server.address.sin_addr) , ntohs(server.address.sin_port));
//                     //Close the socket and mark as 0 in list for reuse 
//                     close( sd );  
//                     server.client_socket[i] = 0;  
//                 }  
                     
//                 //Echo back the message that came in 
//                 else 
//                 {
//                     server.buffer[valread] = '\0';  
//                     send(sd , server.buffer , strlen(server.buffer) , 0 );  
//                 }
//             }
//         }
//     }
// } 