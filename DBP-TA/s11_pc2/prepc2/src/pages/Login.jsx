import React, { useState } from 'react'
import { fetchLogin } from '../services/api'
import { useNavigate } from 'react-router-dom'

const Login = () => {
  const [email, setEmail] = useState("")
  const [password, setPassword] = useState("")

  const navigate = useNavigate();

  const handleClick = async () => {
    try {
      const res = await fetchLogin(email,password)
      
      localStorage.setItem('token', res.data.token); 

      if (res.status === 200){
        navigate('/dashboard')
      }

    } catch (error) {
      console.log(error);
    }
  
  }

  return (
    <>
      
        <label htmlFor="email">Email:</label>
        <input 
          onChange = {(e) => setEmail(e.target.value)}
          type="email" name="email" id="email" required/>

        <label htmlFor="password">Password:</label>
        <input 
          onChange = {(e) => setPassword(e.target.value)}
          type="password" name="password" id="password" />

        <button
          onClick={ handleClick }
        >
          Click me!</button>
      
    </>
  )
}

export default Login