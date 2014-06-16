using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

namespace mainserver
{

    class Program
    {
        private static Mutex _mut = new Mutex();
        private static int i;
        private static List <Sender> _Clients = new List<Sender>();////wtf???
        private static byte[] Buffer { get; set; }
        private static Socket _serverSocket;
                
        
        static void Main(string[] args)
        {
            Thread mainThread = new Thread(()=>serverSetUp());
            mainThread.Start();
                   

        }


        static void serverSetUp()// создание сервера
        {
            
            i = 1;
            _serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _serverSocket.Blocking = true;
            _serverSocket.Bind(new IPEndPoint(IPAddress.Loopback, 1234));
            _serverSocket.Listen(500);
            while (true)
            {
                Console.Write("Server is working!");
                _mut.WaitOne();
                Socket accepted = _serverSocket.Accept();
                _mut.ReleaseMutex();
                _Clients.Add(new Sender(_serverSocket, i, accepted, _Clients, _mut));
                Thread.Sleep(10);
                i++;
            }
           
            
        }

    }



    //класс клиента
    [Serializable()]
    class Sender
    {
        public delegate void ListChangedHandler(Socket serverSocket, List<Sender> Clients, Mutex mut);
        public event ListChangedHandler ListChanged;

        public Socket _clientSocket;
        public static List<int> FriendList = new List <int>();
        private byte[] Buffer { get; set; }
        public int _id;
        public string ClientAddress;
        public string port;
        Thread thMessages;//поток, в котором принимаются сообщения от клиента и отправлются куда надо
        Thread thEvents;// поток, в котором принимаются от сервера сообщения по поводу изменения количества подключенных друзей
        string _strData;
        private int _indicator;

        protected void OnListChanged(Socket serverSocket, List<Sender> Clients, Mutex mut)
        {
            if (ListChanged != null)
            {
                ListChanged(serverSocket, Clients, mut);
            }
        }      

        public Sender(Socket _serverSocket, int i, Socket newClient, List<Sender> Clients, Mutex mut)//constructor
        {
            Console.Write("Connection made!");
            _strData = "";
            _indicator = i;//кому передать сообщение
            _clientSocket = newClient;//сокет подключения к клиенту
            _clientSocket.Blocking = true;
            ClientAddress = ((IPEndPoint)_clientSocket.RemoteEndPoint).Address.ToString();
            port = ((IPEndPoint)_clientSocket.RemoteEndPoint).Port.ToString();
            _id = i;//персональный айдишник
            thMessages = new Thread(() => Messages(_serverSocket, Clients, mut));
            thMessages.Start();
            thEvents = new Thread(() => Events(_serverSocket, Clients, mut));
            thEvents.Start();
            OnListChanged(_serverSocket, Clients, mut);
        }




        public void Messages(Socket _serverSocket, List <Sender> Clients, Mutex mut)// функция обмена данными с клиентом
        {
           Console.Write("Server is listening for the client!");
           while (true)
            {
                Buffer = new Byte[_clientSocket.SendBufferSize];//создаем массив байтов такого же размера,
                                                            //сколько байтов в передаваемых данных
                int BytesRead = _clientSocket.Receive(Buffer);
                byte[] formatted = new byte[BytesRead];// считаем количество байтов, которые были приняты и записаны в буфер
                for (int j = 0; j < BytesRead; j++)
                {
                    formatted[j] = Buffer[j];
                }
                char[] _message = Encoding.ASCII.GetChars(formatted);
                char a = _message[0];
                _indicator = /*_message[0] - '0';*/ int.Parse(_message[0].ToString());
                mut.WaitOne(); 
               if (_indicator == 0)
                {
                    _clientSocket.Close();
                    Clients.Remove(this);
                    Console.Write("Connection broken with " + this._id);
                    OnListChanged(_serverSocket, Clients, mut);
                    // ивент, который заставляет все потоки разослать списки заново
                }
                else
                {
                 
                   int j = 0;
                    _strData = Encoding.ASCII.GetString(formatted);
                    Console.Write(_message);
                    while (_indicator != Clients[j]._id)
                    {
                        j++;
                    }
                    Clients[j].SendMessage(_strData);
                    Console.Write(_strData + "\r\n");
                 }
               mut.ReleaseMutex();
            }
         
        }


      
        public void Events(Socket serverSocket, List <Sender> Clients, Mutex mut)
        {
           
            Console.Write("Server is ready to update FriendList!");
            
                for (int j = 0; j < Clients.Count(); j++)
                {
                     Clients[j].ListChanged += this.SendFriendList;
                }
            
                  
        }
    

        public void SendMessage(string strData)
        {
            strData = "m" + strData;
            byte[] toBytes = Encoding.ASCII.GetBytes(strData);

            _clientSocket.Send(toBytes);//?????? непонятно, ясно ли программе,
                    //что посылать должен сокет сервера, а не подключения
            Console.Write("Message sent!");
            
        }

        public void SendFriendList(Socket serverSocket, List <Sender> Clients, Mutex mut)
        {
            for (int j = 0; j < Clients.Count(); j++)
            {
                FriendList.Add(Clients[j]._id);
            }
            byte[] BufferList  = new byte[(Clients.Count()) * sizeof(int)];//какого размера создавать массив байтов?
          try
            {
                System.Runtime.Serialization.IFormatter formatter = new BinaryFormatter();
                Stream stream = new MemoryStream(BufferList);
                formatter.Serialize(stream, FriendList);
                mut.WaitOne();
                _clientSocket.Send(BufferList);
                mut.ReleaseMutex();
                Console.Write("FriendList updated!");
           }
            catch(IOException)
            {
                Console.Write("FriendList cannot be sent ;C");
            }
           
        }
        
    }


   
}


 








