import React,  {useState } from 'react'
import { fetchLogin } from '../services/api'
import { useNavigate } from 'react-router-dom'

const Login = () => {
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('')
  const navigate = useNavigate()

  const handleSubmit = async(e) => {
    e.preventDefault();
    
    try{
      const res = await fetchLogin(email, password)
      localStorage.setItem('token', res.data.token);
      navigate('/rides')
    } catch(error) {
      console.log(error);
      alert('User o pass incorrect')
    }
  }

  return (
    <>
      <h1>Login</h1>

      <form onSubmit={ handleSubmit }>
        <label htmlFor="email">Email</label>
        <input 
          onChange={(e) => { setEmail(e.target.value) }}
          type="email" id="email" required/>

        <label htmlFor="password">password</label>
        <input 
          onChange={(e) => { setPassword(e.target.value) }}
          type="password" id="password" required/>

        <button>Submit</button>
      </form>

    </>
  )
}

export default Login