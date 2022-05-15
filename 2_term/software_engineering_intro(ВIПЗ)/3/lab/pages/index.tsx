import { PageHeader } from "antd";
import type { NextPage } from "next";
import Head from "next/head";
import { useEffect } from "react";
import { StudentsTable } from "../components/StudentsTable";

const Home: NextPage = () => {
  useEffect(() => {
    // prompt before closing the tab
    window.onbeforeunload = () => "";
  }, []);

  return (
    <div className="site-page-header-ghost-wrapper">
      <Head>
        <title>Students Info</title>
        <meta
          name="description"
          content="Tool for working with students records"
        />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <PageHeader ghost={false} title="Students Panel">
        <main>
          <StudentsTable />
        </main>
      </PageHeader>
    </div>
  );
};

export default Home;
