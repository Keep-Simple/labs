import "antd/dist/antd.css";
import type { AppProps } from "next/app";
import "../styles/Home.css";
import "../styles/global.css";

function MyApp({ Component, pageProps }: AppProps) {
  return <Component {...pageProps} />;
}

export default MyApp;
