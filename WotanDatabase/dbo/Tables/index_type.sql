CREATE TABLE [dbo].[index_type] (
    [id]          INT            IDENTITY (1, 1) NOT NULL,
    [name]        NVARCHAR (50)  NOT NULL,
    [description] NVARCHAR (250) NULL,
    CONSTRAINT [PK_index_type] PRIMARY KEY CLUSTERED ([id] ASC)
);

